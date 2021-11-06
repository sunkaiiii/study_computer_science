//! # Art
//!
//! 一个用来建模艺术概念的代码库

pub use self::kinds::PrimaryColor;
pub use self::kinds::SecndaryColor;
pub use self::utils::mix;

pub mod kinds{
    /// RYB颜色模型的三原色
    /// 
    pub enum PrimaryColor {
        Red,
        Yellow,
        Blue,
    }

    ///RYB模型的调和色
    
    pub enum SecndaryColor {
        Orange,
        Green,
        Purple
    }
}

pub mod utils{
    use crate::kinds::*;

    ///将两种等量的原色混合成调和色
    
    pub fn mix(c1:PrimaryColor,c2:PrimaryColor) -> SecndaryColor{
        SecndaryColor::Green
    }
}