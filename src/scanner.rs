pub struct Scanner {
    chars: Vec<char>,
    char_idx: usize,
    has_error: bool,
    errors: Vec<String>,
}

#[derive(Debug)]
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
            if self.peek_next().is_none() {
                break;
            }

            match ch {
                ' ' | '\0' => self.consume(),
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

        if let Some(c) = self.peek() {
            buffer.push(*c);
            self.consume();
        }

        while self.peek().map_or(false, |c| c.is_ascii_digit()) {
            if let Some(c) = self.peek() {
                buffer.push(*c);
                self.consume();
            }
        }

        // Check for a decimal point
        if self.peek() == Some(&'.') {
            // Ensure the dot is not the last character
            if self.peek_next().map_or(false, |c| c.is_ascii_digit()) {
                buffer.push(*self.peek().unwrap());
                self.consume();
                // Consume digits after the dot
                while self.peek().map_or(false, |c| c.is_ascii_digit()) {
                    buffer.push(*self.peek().unwrap());
                    self.consume();
                }
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
