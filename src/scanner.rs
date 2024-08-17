pub struct Scanner {
    chars: Vec<char>,
    char_idx: usize,
    pub(crate) has_error: bool,
    pub(crate) errors: Vec<String>,
}

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum Token {
    Number(f32),
    LeftParen,
    RightParen,
    Plus,
    Minus,
    Divide,
    Multiply,
}

impl Scanner {
    pub fn new(source: String) -> Scanner {
        Scanner {
            chars: source.chars().collect(),
            char_idx: 0,
            has_error: false,
            errors: vec![],
        }
    }

    pub fn scan(&mut self) -> Vec<Token> {
        let mut tokens: Vec<Token> = vec![];

        while let Some(ch) = self.peek() {
            match ch {
                ' ' | '\0' | '\n' => self.consume(),
                '0'..'9' => {
                    self.consume_number(&mut tokens);
                }
                '+' => {
                    tokens.push(Token::Plus);
                    self.consume();
                }
                '-' => {
                    tokens.push(Token::Minus);
                    self.consume();
                }
                '*' => {
                    tokens.push(Token::Multiply);
                    self.consume();
                }
                '/' => {
                    tokens.push(Token::Divide);
                    self.consume();
                }
                '(' => {
                    tokens.push(Token::LeftParen);
                    self.consume();
                }
                ')' => {
                    tokens.push(Token::RightParen);
                    self.consume();
                }
                _ => {
                    self.has_error = true;
                    self.errors.push(String::from("Invalid char"));
                    self.consume();
                }
            }
        }

        tokens
    }

    fn consume(&mut self) {
        self.char_idx += 1;
    }

    fn consume_number(&mut self, tokens: &mut Vec<Token>) {
        let mut buffer = String::new();

        // Consume the current digit
        if let Some(c) = self.peek() {
            buffer.push(*c);
            self.consume();
        }

        // Consume all next digits
        while self.peek().map_or(false, |c| c.is_ascii_digit()) {
            if let Some(c) = self.peek() {
                buffer.push(*c);
                self.consume();
            }
        }

        // Check for a decimal point
        if self.peek() == Some(&'.') {
            if self.peek_next().map_or(false, |c| c.is_ascii_digit()) {
                buffer.push(*self.peek().unwrap());
                self.consume();
                // Consume digits after the dot
                while self.peek().map_or(false, |c| c.is_ascii_digit()) {
                    buffer.push(*self.peek().unwrap());
                    self.consume();
                }
            } else {
                // Ignore leading decimal
                self.consume();
            }
        }

        let number = buffer.parse::<f32>();

        match number {
            Ok(num) => tokens.push(Token::Number(num)),
            Err(err) => panic!("{}", err),
        }
    }

    fn peek(&self) -> Option<&char> {
        self.chars.get(self.char_idx)
    }

    fn peek_next(&self) -> Option<&char> {
        self.chars.get(self.char_idx + 1)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_single_digit_numbers() {
        let source = "3 + 4".to_string();
        let mut scanner = Scanner::new(source);
        let tokens = scanner.scan();

        assert_eq!(
            tokens,
            vec![Token::Number(3.0), Token::Plus, Token::Number(4.0)]
        );
        assert_eq!(scanner.has_error, false);
        assert!(scanner.errors.is_empty());
    }

    #[test]
    fn test_multiple_digit_numbers() {
        let source = "12 * 34".to_string();
        let mut scanner = Scanner::new(source);
        let tokens = scanner.scan();

        assert_eq!(
            tokens,
            vec![Token::Number(12.0), Token::Multiply, Token::Number(34.0)]
        );
        assert_eq!(scanner.has_error, false);
        assert!(scanner.errors.is_empty());
    }

    #[test]
    fn test_decimal_numbers() {
        let source = "12.34 + 56.78".to_string();
        let mut scanner = Scanner::new(source);
        let tokens = scanner.scan();

        assert_eq!(
            tokens,
            vec![Token::Number(12.34), Token::Plus, Token::Number(56.78)]
        );
        assert_eq!(scanner.has_error, false);
        assert!(scanner.errors.is_empty());
    }

    #[test]
    fn test_parentheses() {
        let source = "(1 + 2) * 3".to_string();
        let mut scanner = Scanner::new(source);
        let tokens = scanner.scan();

        assert_eq!(
            tokens,
            vec![
                Token::LeftParen,
                Token::Number(1.0),
                Token::Plus,
                Token::Number(2.0),
                Token::RightParen,
                Token::Multiply,
                Token::Number(3.0)
            ]
        );
        assert_eq!(scanner.has_error, false);
        assert!(scanner.errors.is_empty());
    }

    #[test]
    fn test_division_and_subtraction() {
        let source = "10 / 2 - 3".to_string();
        let mut scanner = Scanner::new(source);
        let tokens = scanner.scan();

        assert_eq!(
            tokens,
            vec![
                Token::Number(10.0),
                Token::Divide,
                Token::Number(2.0),
                Token::Minus,
                Token::Number(3.0)
            ]
        );
        assert_eq!(scanner.has_error, false);
        assert!(scanner.errors.is_empty());
    }

    #[test]
    fn test_invalid_character() {
        let source = "3 + 4 @".to_string();
        let mut scanner = Scanner::new(source);
        let tokens = scanner.scan();

        assert_eq!(
            tokens,
            vec![Token::Number(3.0), Token::Plus, Token::Number(4.0)]
        );
        assert_eq!(scanner.has_error, true);
        assert_eq!(scanner.errors, vec![String::from("Invalid char")]);
    }

    #[test]
    fn test_trailing_space() {
        let source = "7 * 8 ".to_string();
        let mut scanner = Scanner::new(source);
        let tokens = scanner.scan();

        assert_eq!(
            tokens,
            vec![Token::Number(7.0), Token::Multiply, Token::Number(8.0)]
        );
        assert_eq!(scanner.has_error, false);
        assert!(scanner.errors.is_empty());
    }

    #[test]
    fn test_incomplete_decimal() {
        let source = "3. + 4".to_string();
        let mut scanner = Scanner::new(source);
        let tokens = scanner.scan();

        // This should still parse "3." as 3.0 and continue with the rest
        assert_eq!(
            tokens,
            vec![Token::Number(3.0), Token::Plus, Token::Number(4.0)]
        );
        assert_eq!(scanner.has_error, false);
        assert!(scanner.errors.is_empty());
    }
}
