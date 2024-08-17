use crate::scanner::Token;

pub struct Parser {
    tokens: Vec<Token>,
    read_idx: usize,
    pub(crate) has_error: bool,
    pub(crate) errors: Vec<String>,
}

trait Precedence {
    fn precedence(&self) -> u8;
}

impl Precedence for Token {
    fn precedence(&self) -> u8 {
        match self {
            Token::Plus | Token::Minus => 1,
            Token::Divide | Token::Multiply => 2,
            _ => 0,
        }
    }
}

impl Parser {
    pub fn new(tokens: Vec<Token>) -> Parser {
        Parser {
            tokens,
            read_idx: 0,
            has_error: false,
            errors: vec![],
        }
    }

    pub fn parse(&mut self) -> Vec<Token> {
        let mut tokens: Vec<Token> = vec![];
        let mut operators: Vec<Token> = vec![];

        while let Some(token) = self.peek() {
            match token {
                Token::Number(number) => {
                    tokens.push(Token::Number(*number));
                    self.consume();
                }
                Token::LeftParen => {
                    operators.push(Token::LeftParen);
                    self.consume();
                }
                Token::RightParen => {
                    // FIXME
                    while let Some(last) = operators.last() {
                        if *last == Token::LeftParen {
                            operators.pop();
                            self.consume();
                            break;
                        } else {
                            tokens.push(operators.pop().unwrap());
                            self.consume();
                        }
                    }

                    if operators.last().is_none() || operators.last() != Some(&Token::LeftParen) {
                        self.has_error = true;
                        self.errors.push("Mismatched parentheses".to_string());
                    }
                }
                Token::Plus | Token::Minus | Token::Divide | Token::Multiply => loop {
                    let current = self.peek().unwrap();
                    let last = operators.last();
                    match last {
                        Some(last) => {
                            if last.precedence() >= current.precedence() {
                                tokens.push(operators.pop().unwrap());
                                operators.push(*current);
                                self.consume();
                            } else {
                                operators.push(*current);
                                self.consume();
                                break;
                            }
                        }
                        None => {
                            operators.push(*current);
                            self.consume();
                            break;
                        }
                    }
                },
            }
        }

        while !operators.is_empty() {
            tokens.push(operators.pop().unwrap());
        }

        tokens
    }

    fn consume(&mut self) {
        self.read_idx += 1;
    }

    fn peek(&self) -> Option<&Token> {
        self.tokens.get(self.read_idx)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::scanner::{Scanner, Token};

    fn scan_tokens(source: &str) -> Vec<Token> {
        let mut scanner = Scanner::new(source.to_string());
        scanner.scan()
    }

    #[test]
    fn test_single_number() {
        let tokens = scan_tokens("3");
        let mut parser = Parser::new(tokens);
        let output = parser.parse();

        assert_eq!(output, vec![Token::Number(3.0)]);
    }

    #[test]
    fn test_simple_addition() {
        let tokens = scan_tokens("3+4.5");
        let mut parser = Parser::new(tokens);
        let output = parser.parse();

        assert_eq!(
            output,
            vec![Token::Number(3.0), Token::Number(4.5), Token::Plus]
        );
    }

    #[test]
    fn test_addition_and_multiplication() {
        let tokens = scan_tokens("3+4*2");
        let mut parser = Parser::new(tokens);
        let output = parser.parse();

        assert_eq!(
            output,
            vec![
                Token::Number(3.0),
                Token::Number(4.0),
                Token::Number(2.0),
                Token::Multiply,
                Token::Plus
            ]
        );
    }

    #[test]
    fn test_expression_with_parentheses() {
        let tokens = scan_tokens("(3+4.2)*2");
        let mut parser = Parser::new(tokens);
        let output = parser.parse();

        assert_eq!(
            output,
            vec![
                Token::Number(3.0),
                Token::Number(4.2),
                Token::Plus,
                Token::Number(2.0),
                Token::Multiply
            ]
        );
    }

    #[test]
    fn test_complex_expression() {
        let tokens = scan_tokens("3.7+4*(2.91-1)/5.0");
        let mut parser = Parser::new(tokens);
        let output = parser.parse();

        assert_eq!(
            output,
            vec![
                Token::Number(3.7),
                Token::Number(4.0),
                Token::Number(2.91),
                Token::Number(1.0),
                Token::Minus,
                Token::Multiply,
                Token::Number(5.0),
                Token::Divide,
                Token::Plus
            ]
        );
    }
}
