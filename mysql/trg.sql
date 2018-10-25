*************************** 1. row ***************************
             Trigger: fun_article_filter_insert
               Event: INSERT
               Table: t_fun_article_filter
           Statement: BEGIN
    DECLARE after_vals VARCHAR(1023) DEFAULT NULL;
    SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"fun_article_id":', NEW.fun_article_id, ''));
    SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"src":', NEW.src, ''));
    SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"article_type":', NEW.article_type, ''));
    SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"is_valid":', NEW.is_valid, ''));
    INSERT IGNORE INTO t_cron_queue(`source`, `op`, `key`, `value`)
      VALUES('t_fun_article_filter', 'insert', CONCAT('{"id":', NEW.id, '}'),
             CONCAT('{"after":{"filterInfo":{', after_vals, '}}}'));
  END
              Timing: AFTER
             Created: NULL
            sql_mode: 
             Definer: video@10.123.98.31
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
*************************** 2. row ***************************
             Trigger: fun_article_filter_update
               Event: UPDATE
               Table: t_fun_article_filter
           Statement: BEGIN
    DECLARE after_vals VARCHAR(1023) DEFAULT NULL;
    SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"fun_article_id":', NEW.fun_article_id, ''));
    SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"src":', NEW.src, ''));
    SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"article_type":', NEW.article_type, ''));
    SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"is_valid":', NEW.is_valid, ''));
    INSERT IGNORE INTO t_cron_queue(`source`, `op`, `key`, `value`)
      VALUES('t_fun_article_filter', 'update', CONCAT('{"id":', NEW.id, '}'),
             CONCAT('{"after":{"filterInfo":{', after_vals, '}}}'));
  END
              Timing: AFTER
             Created: NULL
            sql_mode: 
             Definer: video@10.123.98.31
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
*************************** 3. row ***************************
             Trigger: fun_article_filter_delete
               Event: DELETE
               Table: t_fun_article_filter
           Statement: BEGIN
    DECLARE after_vals VARCHAR(1023) DEFAULT NULL;
    SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"fun_article_id":', OLD.fun_article_id, ''));
    SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"src":', OLD.src, ''));
    SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"article_type":', OLD.article_type, ''));
    SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"is_valid":', 0, ''));
    INSERT IGNORE INTO t_cron_queue(`source`, `op`, `key`, `value`)
      VALUES('t_fun_article_filter', 'delete', CONCAT('{"id":', OLD.id, '}'),
             CONCAT('{"after":{"filterInfo":{', after_vals, '}}}'));
  END
              Timing: AFTER
             Created: NULL
            sql_mode: 
             Definer: video@10.123.98.31
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
*************************** 4. row ***************************
             Trigger: video_filter_insert
               Event: INSERT
               Table: t_video_filter
           Statement: BEGIN
    INSERT IGNORE INTO t_cron_queue(`source`, `op`, `key`)
      VALUES('t_video_filter', 'insert', CONCAT('{"video_id":', NEW.video_id, '}'));
  END
              Timing: AFTER
             Created: NULL
            sql_mode: 
             Definer: video@10.123.98.31
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
*************************** 5. row ***************************
             Trigger: video_filter_delete
               Event: DELETE
               Table: t_video_filter
           Statement: BEGIN
    INSERT IGNORE INTO t_cron_queue(source, op, `key`)
      VALUES('t_video_filter', 'delete', CONCAT('{"video_id":', OLD.video_id, '}'));
  END
              Timing: AFTER
             Created: NULL
            sql_mode: 
             Definer: video@10.123.98.31
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
