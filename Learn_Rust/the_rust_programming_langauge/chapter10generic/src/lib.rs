pub mod aggregator{
    use std::fmt::Display;
    pub struct NewsArticle{
        pub headline:String,
        pub location:String,
        pub author:String,
        pub content:String,
    }
    
    impl Summary for NewsArticle {
        fn summarize(&self)->String{
            return format!("{}, by {} ({})", self.headline, self.author, self.location);
        }
    }
    
    pub trait Summary {
        fn summarize(&self)->String{
            String::from("(Read more...)")
        }
    }
    
    pub struct Tweet{
        pub username:String,
        pub content:String,
        pub reply:bool,
        pub retweet:bool,
    }
    
    impl Summary for Tweet {
        fn summarize(&self) ->String {
            format!("{}: {}", self.username, self.content)
        }
    }

    pub fn notify(item:impl Summary){
        println!("Breaking news! {}",item.summarize());
    }

    pub fn returns_summarizable()->impl Summary{
        Tweet{
            username:"horse".to_string(),
            content: "of course, as you probably already know, people".to_string(),
            reply:false,
            retweet:false,
        }
    }

    struct Pair<T>{
        x:T,
        y:T,
    }

    impl <T> Pair<T> {
        fn new(x:T,y:T)->Self{
            Self{
                x,y
            }
        }
    }

    impl <T:Display+PartialOrd> Pair<T> {
        fn cmp_display(&self){
            if self.x>=self.y{
                println!("The largest member is x={}",self.x);
            }else{
                println!("The largest member is y={}",self.y)
            }
        }
    }

    //同时使用泛型参数、trait约束与生命周期
    pub fn longest_with_an_announcement<'a,T>(x:&'a str, y: &'a str, ann:T)->&'a str where T:Display{
        println!("Announcement! {}",ann);
        if x.len() > y.len(){
            x
        }else{
            y
        }
    }
}
