fn main() {
     let s1 = String::from("hello");
    //  let s2 = s1; //所有权转移（move）
    let s2 = s1.clone(); //深度拷贝

    let mut  s = String::from("Hello"); //变量s进入作用域
    let len = calculate_length(&s); //引用传递，不转义所有权
    println!("The length of '{}' is {}.",s,len);
    extend_string(&mut s); //使用可变引用
    let s3 = &s;
    let s4 = &s; //允许多个不可变引用
    takes_ownership(s); //s的值被移动进了函数
     //从这里开始，就不可以用s了

    let x =5; //x进入作用域
    makes_copy(5); //由于i32支持copy，所以之后还可以用x

     println!("{} world",s1);

     println!("word is {}",first_word(&String::from("Can you please")));
}

fn takes_ownership(some_string:String){
     println!("{}",some_string);
} //some_string离开作用于，drop函数自动调用

fn makes_copy(some_integer:i32){
     println!("{}",some_integer);
}

fn calculate_length(s:&String)->usize{
     return s.len();
}

fn extend_string(s:&mut String){
     s.push_str(" world");
}

//字符串切片
fn first_word(s:&str)->&str{
     let bytes = s.as_bytes();
     for (i,&item) in bytes.iter().enumerate() {
         if item == b' '{
              return &s[0..i];
         }
     }
     return &s[..];
}