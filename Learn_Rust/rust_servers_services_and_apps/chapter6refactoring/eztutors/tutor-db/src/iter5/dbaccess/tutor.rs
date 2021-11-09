use crate::errors::EzyTutorError;
use crate::models::tutor::{NewTutor, Tutor, UpdateTutor};
use sqlx::postgres::PgPool;
pub async fn get_all_tutors_db(pool: &PgPool) -> Result<Vec<Tutor>, EzyTutorError> {
    // Prepare SQL statement
    let tutor_rows = sqlx::query!(
        "SELECT tutor_id, tutor_name, tutor_pic_url, tutor_profile
        FROM ezy_tutor_c6"
    )
    .fetch_all(pool)
    .await?;
    // Extract result
    let tutors: Vec<Tutor> = tutor_rows
        .iter()
        .map(|tutor_row| Tutor {
            tutor_id: tutor_row.tutor_id,
            tutor_name: tutor_row.tutor_name.clone(),
            tutor_pic_url: tutor_row.tutor_pic_url.clone(),
            tutor_profile: tutor_row.tutor_profile.clone(),
        })
        .collect();
    match tutors.len() {
        0 => Err(EzyTutorError::NotFound("No tutors found".into())),
        _ => Ok(tutors),
    }
}

pub async fn get_tutor_details_db(pool: &PgPool, tutor_id: i32) -> Result<Tutor, EzyTutorError> {
    // Prepare SQL statement
    let tutor_row = sqlx::query!(
        "SELECT tutor_id, tutor_name, tutor_pic_url,
        tutor_profile FROM ezy_tutor_c6 where tutor_id = $1",
        tutor_id
    )
    .fetch_one(pool)
    .await
    .map(|tutor_row| Tutor {
        tutor_id: tutor_row.tutor_id,
        tutor_name: tutor_row.tutor_name,
        tutor_pic_url: tutor_row.tutor_pic_url,
        tutor_profile: tutor_row.tutor_profile,
    })
    .map_err(|_err| EzyTutorError::NotFound("Tutor id not found".into()))?;
    Ok(tutor_row)
}

pub async fn post_new_tutor_db(pool: &PgPool, new_tutor: NewTutor) -> Result<Tutor, EzyTutorError> {
    // sql prep
    let row = sqlx::query!(
        "
        INSERT INTO ezy_tutor_c6 (tutor_name, tutor_pic_url, tutor_profile) VALUES ($1,$2,$3)
        RETURNING tutor_id",
        new_tutor.tutor_name,
        new_tutor.tutor_pic_url,
        new_tutor.tutor_profile
    )
    .fetch_one(pool)
    .await?;
    Ok(Tutor {
        tutor_id: row.tutor_id,
        tutor_name: new_tutor.tutor_name,
        tutor_pic_url: new_tutor.tutor_pic_url,
        tutor_profile: new_tutor.tutor_profile,
    })
}

pub async fn update_tutor_details_db(
    pool: &PgPool,
    tutor_id: i32,
    tutor: UpdateTutor,
) -> Result<String, EzyTutorError> {
    // Retrieve the existing row.
    let curr_tutor = sqlx::query_as!(
        Tutor,
        "SELECT * FROM ezy_tutor_c6 WHERE tutor_id = $1",
        tutor_id
    )
    .fetch_one(pool)
    .await?;

    // Check what has been provided (although this is more a PATCH use case).
    let name = if let Some(name) = tutor.tutor_name {
        name
    } else {
        curr_tutor.tutor_name
    };
    let pic_url = if let Some(pic_url) = tutor.tutor_pic_url {
        pic_url
    } else {
        curr_tutor.tutor_pic_url
    };
    let profile = if let Some(profile) = tutor.tutor_profile {
        profile
    } else {
        curr_tutor.tutor_profile
    };

    sqlx::query!(
        "
    UPDATE ezy_tutor_c6 SET tutor_name=$1, tutor_pic_url=$2, tutor_profile=$3",
        name,
        pic_url,
        profile
    )
    .execute(pool)
    .await
    .map(|_res| "Tutor has been updated".into())
    .map_err(|_err| EzyTutorError::NotFound("Tutor not found".into()))
}

pub async fn delete_tutor_db(pool: &PgPool, tutor_id: i32) -> Result<String, EzyTutorError> {
    sqlx::query!("DELETE FROM ezy_tutor_c6 WHERE tutor_id = $1", tutor_id)
        .execute(pool)
        .await
        .map(|_res| "Tutor has been deleted".into())
        .map_err(|_err| EzyTutorError::NotFound("Tutor not found".into()))
}
