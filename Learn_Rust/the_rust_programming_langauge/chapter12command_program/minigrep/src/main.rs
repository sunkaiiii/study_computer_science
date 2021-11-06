use std::process;
use std::{env, fs};
use minigrep::Config;
fn main() {
    //收集参数
    let args:Vec<String> = env::args().collect();
    let config = Config::new(&args).unwrap_or_else(|err|{
        eprintln!("Problem parsing arguments: {}",err);
        process::exit(1);
    });

    if let Err(e) = minigrep::run(config){
        eprintln!("Application error: {}",e);
        process::exit(1);
    }
}