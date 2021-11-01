use std::slice::SliceIndex;
use std::collections::HashMap;
fn main() {
    let v:Vec<i32> = Vec::new(); //创建动态数组
    //使用宏
    let mut v = vec![1,2,3];
    v.push(5); //更新数组
    let third = &v[2];
    //第二种方式获取元素
    match v.get(2) {
        Some(third) => println!("The third is {}",third),
        None => println!("There is no third element"),
    }

    for i in &v{
        println!("{}",i);
    }

    //可以修改可变动态数组
    for i in &mut v {
        *i+=50;
    }

    //使用enum来存储不同的类型
    let row = vec![
        SpreadsheetCell::Int(3),
        SpreadsheetCell::Text(String::from("blue")),
        SpreadsheetCell::Float(10.12),
    ];


    //字符串遍历
    for c in "这种这种付付翁过".chars(){
        println!("{}",c);
    }

    //使用hashmap
    let mut scores = HashMap::new();
    scores.insert("Blue".to_string(), 10);
    scores.insert("Yello".to_string(), 50);

    let teams = vec!["Blue".to_string(),"Yello".to_string()];
    let initial_score = vec![10,50];
    let scores:HashMap<_,_> = teams.iter().zip(initial_score.iter()).collect();
    let field_name = "Color".to_string();
    let field_value = 50;
    //遍历，顺序不定
    for (key,value) in &scores{
        println!("{}: {}",key,value);
    }
    let mut scores = HashMap::new();
    scores.insert(field_name, field_value);
    //field_name将不再可用
    // println!("{}",field_name);
    scores.insert("Blue".to_string(), 10);
    //直接替换旧值
    scores.insert("Blue".to_string(), 25);
    println!("{:?}",scores);
    //entry方法在键不存在的时候插入数据
    scores.entry("Blue".to_string()).or_insert(50);
    scores.entry("Yellow".to_string()).or_insert(10);
    println!("{:?}",scores);
    let value = scores.entry("Yellow".to_string()).or_insert(10);
    *value += 1;
    println!("{:?}",scores);
}

enum SpreadsheetCell {
    Int(i32),
    Float(f64),
    Text(String),
}
