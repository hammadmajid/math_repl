use clap::Parser;
use std::{
    io::{stdin, Write},
    process::exit,
};

mod parser;
mod scanner;

#[derive(Parser)]
#[command(version, about, long_about = None)]
struct Cli {
    expression: Option<String>,
}

fn main() {
    let cli = Cli::parse();

    match cli.expression {
        Some(expression) => evaluate(expression),
        None => repl(),
    }
}

fn evaluate(expression: String) {
    let mut scanner = scanner::Scanner::new(expression);

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

fn repl() -> ! {
    loop {
        print!("= ");
        std::io::stdout().flush().unwrap();

        let mut line = String::new();
        match stdin().read_line(&mut line) {
            Ok(_) => evaluate(line),
            Err(err) => {
                eprintln!("{}", err);
                exit(65)
            }
        }
    }
}
