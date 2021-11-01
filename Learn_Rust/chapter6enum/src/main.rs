enum IpAddrKind{
    V4,
    V6,
}

//枚举允许直接关联的数据嵌入枚举内
enum IpAddrEnum {
    V4(u8,u8,u8,u8),
    V6(String),
}

enum Message{
    Quit,
    Move{x:i32,y:i32},
    Write(String),
    ChangeColor(i32,i32,i32),
}

//枚举的impl
impl Message {
    fn call(&self){

    }
}

struct IpAddr{
    kind:IpAddrKind,
    address:String,
}

#[derive(Debug)]
enum UsState {
    Alabama,
    Alaska,
}

enum Coin {
    Penny,
    Nikel,
    Dime,
    Quarter(UsState),
}

fn main() {
    let home = IpAddr{
        kind:IpAddrKind::V4,
        address:String::from("127.0.0.1"),
    };
    let loopback = IpAddr{
        kind:IpAddrKind::V6,
        address:String::from("::1"),
    };

    let home = IpAddrEnum::V4(127,0,0,1);
    let loopback = IpAddrEnum::V6(String::from("::1"));
    let m = Message::Write(String::from("Hello"));
    m.call();

    value_in_cents(Coin::Quarter(UsState::Alaska));

    let five = Some(5);
    let six = plus_one(five);
    let none = plus_one(None);
}

fn route(ip_type:IpAddrKind){}

fn value_in_cents(coin:Coin)->u32{
    match coin {
        Coin::Penny=>1,
        Coin::Nikel=>5,
        Coin::Dime=>10,
        Coin::Quarter(state)=>{
            println!("state quater from {:?}!",state);
            25
        },
    }
}

//匹配Optional<T>
fn plus_one(x:Option<i32>)->Option<i32>{
    match x {
        None=>None,
        Some(i)=>Some(i+1),
    }
}