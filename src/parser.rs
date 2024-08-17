use crate::scanner::Token;

pub struct Parser {
    tokens: Vec<Token>,
    read_idx: usize,
    pub(crate) has_error: bool,
    pub(crate) errors: Vec<String>,
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
