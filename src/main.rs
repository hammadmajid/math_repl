use clap::Parser;
use std::process::exit;

mod parser;
mod scanner;

#[derive(Parser)]
#[command(version, about, long_about = None)]
struct Cli {
    expression: String,
}

fn main() {
    let cli = Cli::parse();
    let mut scanner = scanner::Scanner::new(cli.expression);

    let tokens = scanner.scan();

    if scanner.has_error {
        for err in scanner.errors {
            eprintln!("{err}");
        }
        exit(65);
    }

    let mut parser = parser::Parser::new(tokens);

    let parsed = parser.parse();

    if parser.has_error {
        for err in parser.errors {
            eprintln!("{err}");
        }
        exit(65);
    }

    for token in parsed {
        println!("{:?}", token);
    }
}
