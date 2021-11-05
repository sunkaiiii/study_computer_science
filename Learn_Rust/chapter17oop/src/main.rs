use chapter17oop::{Button,Screen,SelectBox};
use chapter17oop::Post;
use chapter17oop::Post2;
fn main() {
    let screen = Screen{
        components:vec![
            Box::new(SelectBox {
                width: 75,
                height: 10,
                options: vec![
                    String::from("Yes"),
                    String::from("Maybe"),
                    String::from("No")
], }),
            Box::new(Button {
                width: 50,
        height: 10,
                label: String::from("OK"),
            }),
        ],
    };
    screen.run();

    //实现状态模式
    // 1. 在新建博客文章时生成一份空白的草稿文档。
    // 2. 在草稿撰写完毕后，请求对这篇草稿状态的文章进行审批。
    // 3. 在文章通过审批后正式对外发布。
    // 4. 仅返回并打印成功发布后的文章，而不能意外地发布没有通过 审批的文章。
    let mut post = Post::new();
    post.add_text("I ate a salad for lunch today");
    assert_eq!("", post.content()); post.request_review();
    assert_eq!("", post.content());
    post.approve();
    assert_eq!("I ate a salad for lunch today", post.content());

    //状态模式的另一种实现
    let mut post = Post2::new();
    post.add_text("I ate a salad for lunch today");
    let post = post.request_review();
    let post = post.approve();
    assert_eq!("I ate a salad for lunch today", post.content());
}
