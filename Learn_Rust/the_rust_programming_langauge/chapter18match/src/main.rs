enum Color {
    Rgb(i32, i32, i32),
    Hsv(i32, i32, i32)
 }
 enum Message {
     Quit,
     Move { x: i32, y: i32 },
     Write(String),
     ChangeColor(Color),
 }
 struct Point {
    x: i32,
    y: i32,
    z: i32, 
}

enum Notification {
    Hello {id:i32},
}

fn main() {
    let favorite_color: Option<&str> = None;
    let is_tuesday = false;
    let age: Result<u8, _> = "34".parse();
    //混合使用if let、else if、else if let和else
    if let Some(color) = favorite_color{
        println!("Using your favorite color, {}, as the background", color);
    }else if is_tuesday{
        println!("Tuesday is green day!");
    }else if let Ok(age) = age{
        if age>30{
            println!("Using purple as the background color");
        }else{
            println!("Using orange as the background color");
        }
    }else{
        println!("Using blue as the background color");
    }

    let mut stack = Vec::new();
    stack.push(1);
    stack.push(2);
    stack.push(3);
    while let Some(top) = stack.pop(){
        println!("{}",top);
    }

    //解构嵌套
    let msg = Message::ChangeColor(Color::Hsv(0, 160, 255));
    match msg {
        Message::ChangeColor(Color::Rgb(r, g, b)) => {
            println!("Change the color to red {}, green {}, and blue {}", r, g, b)
        },
        Message::ChangeColor(Color::Hsv(h, s, v)) => {
            println!("Change the color to hue {}, saturation {}, and value {}", h, s,v)
        }
        _ => () }

    //使用..忽略剩余部分
    let origin = Point { x: 0, y: 0, z: 0 };
    match origin {
        Point { x, .. } => println!("x is {}", x),
    }
    let numbers = (2, 4, 8, 16, 32);
    match numbers {
        (first,..,last)=>{
            println!("some numbers: {}, {}",first,last);
        }
    }

    //使用匹配守卫添加额外条件
    let num = Some(4);

    match num {
        Some(x) if x<5=>println!("less than five: {}",x),
        Some(x) => println!("{}",x),
        None=>(),
    }

    let x = 4;
    let y = false;

    match x{
        4|5|6 if y => println!("yes"),
        _ => println!("no"),
    }

    //@绑定
    let notification = Notification::Hello{id:5};
    match notification {
        Notification::Hello {id:id_variable @ 3..=7}=>{
            println!("Found an id in range: {}", id_variable)
        },
        Notification::Hello { id: 10..=12 }=>{
            println!("Found an id in another range")
        },
        Notification::Hello{id}=>{
            println!("Found some other id: {}", id)
        },
    }
}
