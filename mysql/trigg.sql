+----------------+-------------+------+-----+-------------------+-----------------------------+
| Field          | Type        | Null | Key | Default           | Extra                       |
+----------------+-------------+------+-----+-------------------+-----------------------------+
| id             | int(11)     | NO   | PRI | NULL              | auto_increment              |
| fun_article_id | bigint(20)  | NO   | MUL | 0                 |                             |
| src            | int(11)     | NO   |     | 0                 |                             |
| article_type   | int(4)      | NO   |     | 0                 |                             |
| update_time    | timestamp   | NO   |     | CURRENT_TIMESTAMP | on update CURRENT_TIMESTAMP |
| guid           | varchar(50) | NO   |     |                   |                             |
| last_user      | varchar(50) | YES  |     |                   |                             |
| is_valid       | tinyint(1)  | YES  |     | 1                 |                             |
+----------------+-------------+------+-----+-------------------+-----------------------------+
