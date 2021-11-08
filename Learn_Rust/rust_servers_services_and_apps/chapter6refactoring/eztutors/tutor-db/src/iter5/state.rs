use std::sync::Mutex;

use sqlx::PgPool;

use crate::handlers::{course::*, general::*};

pub struct AppState {
  pub health_check_response: String,
  pub visit_count: Mutex<u32>,
  pub db: PgPool,
}