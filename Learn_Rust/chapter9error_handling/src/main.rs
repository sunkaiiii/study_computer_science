use core::panic;
use std::fs::File;
use std::io::{ErrorKind, Read};
use std::io;
fn main() {
    // panic!("crash and burn");

    let f = File::open("hello.txt");
    let f = match f {
        Ok(file)=>file,
        Err(error)=>match error.kind() {
            ErrorKind::NotFound => match File::create("hello.txt") {
                Ok(fc)=>fc,
                Err(e)=>panic!("Tried to create file but there was a problem: {:?}",e),
            },
            other_error=>panic!("There was a problem opening the file: {:?}",other_error),
        }
    };
    //使用unwrap来替代match表达式
    let f = File::open("hello.txt").unwrap();

    //使用expect表达式
    // let f = File::open("not_a_file.txt").expect("Failed to open this file");

    let read_result = read_username_from_file();
    match read_result {
        Ok(s)=>println!("{}",s),
        Err(_)=>println!("Cannot read file"),
    };
    let read_result = read_username_from_file2();

}

//将错误传播给调用者
fn read_username_from_file()->Result<String,io::Error>{
    let f = File::open("hello.txt");
    let mut f = match f{
        Ok(file)=>file,
        Err(e)=>return Err(e),
    };
    let mut s = String::new();
    return match f.read_to_string(&mut s){
        Ok(_)=>Ok(s),
        Err(e)=>Err(e),
    };
}

//使用问号描述符进行错误处理
fn read_username_from_file2() -> Result<String,io::Error>{
    let mut s = String::new();
    File::open("hello.txt")?.read_to_string(&mut s)?;
    //如果不是用于演示，可以直接调用
    // use std::fs;
    // fs::read_to_string("hello.txt");
    Ok(s)
}