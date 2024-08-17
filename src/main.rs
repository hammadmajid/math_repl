use clap::Parser;

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
    } else {
        for token in tokens {
            println!("{:?}", token);
        }
    }
}
