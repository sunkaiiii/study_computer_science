#[derive(Debug)] //注解派生Debug trait
struct User{
    username:String,
    email:String,
    sign_in_count:u64,
    active:bool
}

impl User {
    fn get_email_name(&self)->String{
        return self.email.split("@").take(1).collect();
    }

    fn create_dummy_user()->User{
        User { username: String::from(""), email: String::from(""), sign_in_count: 0, active: false }
    } //关联函数
}
fn main() {
    let user1 = User{email:String::from("11@qq.com"),username:String::from("aaa"),sign_in_count: 0,active: true};
    let user2= User{
        email:String::from("ddd@qq.com"),
        ..user1
    }; //简化初始化

    println!("user2 is {:?}",user2);
    println!("email is {}",user2.get_email_name());
    println!("dummy user is {:?}",User::create_dummy_user());
}
