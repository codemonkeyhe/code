*************************** 1. row ***************************
             Trigger: fun_insert
               Event: INSERT
               Table: t_fun
           Statement: BEGIN
declare owner_name varchar(128);
declare owner_icon varchar(256);
declare owner_type int(3);
select name, icon, type into owner_name, owner_icon, owner_type from t_fun_owner where id = NEW.fun_owner_id;
    INSERT IGNORE INTO t_cron_queue(source, op, `key`, value)
      VALUES('t_fun', 'insert', CONCAT('{"fun_id":', NEW.id, '}'),
  CONCAT('{"user_type":',owner_type, ',"user_id":"', NEW.fun_owner_id, '","user_name":"',owner_name, '","user_icon":"',owner_icon, '","content_type":',NEW.content_type, 
  ',"content_word":"',NEW.content_word,'","content_img_url":"',NEW.content_img_url, '","content_url":"',NEW.content_url,'","update_time":"',NEW.update_time, '"}'));
  END
              Timing: AFTER
             Created: NULL
            sql_mode: 
             Definer: video@10.123.98.31
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
*************************** 2. row ***************************
             Trigger: fun_update
               Event: UPDATE
               Table: t_fun
           Statement: BEGIN
    DECLARE after_vals VARCHAR(65535) DEFAULT NULL;
declare owner_name varchar(128);
declare owner_icon varchar(256);
declare owner_type int(3);

    IF NEW.fun_owner_id <> OLD.fun_owner_id THEN
  select name, icon, type into owner_name, owner_icon, owner_type from t_fun_owner where id = NEW.fun_owner_id;
  SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"user_id":"', REPLACE(NEW.fun_owner_id, '"', '\"'), '"'));
  SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"user_type":', REPLACE(owner_type, '"', '\"'), ''));
      SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"user_name":"', REPLACE(owner_name, '"', '\"'), '"'));
  SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"user_icon":"', REPLACE(owner_icon, '"', '\"'), '"'));
    END IF;

IF NEW.content_type <> OLD.content_type THEN
      SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"content_type":', REPLACE(NEW.content_type, '"', '\"'), ''));
    END IF;

IF NEW.content_word <> OLD.content_word THEN
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"content_word":"', REPLACE(NEW.content_word, '"', '\"'), '"'));
END IF;

IF NEW.content_img_url <> OLD.content_img_url THEN
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"content_img_url":"', REPLACE(NEW.content_img_url, '"', '\"'), '"'));
END IF;

IF NEW.content_url <> OLD.content_url THEN
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"content_url":"', REPLACE(NEW.content_url, '"', '\"'), '"'));
END IF;

IF NEW.update_time <> OLD.update_time THEN
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"update_time":"', REPLACE(NEW.update_time, '"', '\"'), '"'));
END IF;
IF after_vals <> '' THEN
      INSERT IGNORE INTO t_cron_queue(source, op, `key`, value) VALUES(
        't_fun', 'update', CONCAT('{"fun_id":', NEW.id, '}'),
        CONCAT('{"after":{', after_vals, '}}'));
    END IF;
  END
              Timing: AFTER
             Created: NULL
            sql_mode: 
             Definer: video@10.123.98.31
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
*************************** 3. row ***************************
             Trigger: fun_delete
               Event: DELETE
               Table: t_fun
           Statement: BEGIN
    INSERT IGNORE INTO t_cron_queue(source, op, `key`)
      VALUES('t_fun', 'delete', CONCAT('{"fun_id":', OLD.id, '}'));
  END
              Timing: AFTER
             Created: NULL
            sql_mode: 
             Definer: video@10.123.98.31
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
*************************** 4. row ***************************
             Trigger: fun_article_delete
               Event: DELETE
               Table: t_fun_article
           Statement: BEGIN
INSERT IGNORE INTO t_fun_cron_queue(source, op, `key`)
VALUES('t_fun_article', 'delete', CONCAT('{"fun_article_id":', OLD.fun_article_id, '}'));
END
              Timing: AFTER
             Created: NULL
            sql_mode: 
             Definer: funuser@%
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
*************************** 5. row ***************************
             Trigger: fun_article_filter_insert
               Event: INSERT
               Table: t_fun_article_filter
           Statement: BEGIN
DECLARE after_vals VARCHAR(1023) DEFAULT NULL;
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"fun_article_id":', NEW.fun_article_id, ''));
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"src":', NEW.src, ''));
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"article_type":', NEW.article_type, ''));
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"is_valid":', NEW.is_valid, ''));
INSERT IGNORE INTO t_fun_cron_queue(`source`, `op`, `key`, `value`)
VALUES('t_fun_article_filter', 'insert', CONCAT('{"id":', NEW.id, '}'),
    CONCAT('{"after":{"filterInfo":{', after_vals, '}}}'));
END
              Timing: AFTER
             Created: NULL
            sql_mode: 
             Definer: funuser@%
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
*************************** 6. row ***************************
             Trigger: fun_article_filter_update
               Event: UPDATE
               Table: t_fun_article_filter
           Statement: BEGIN
DECLARE after_vals VARCHAR(1023) DEFAULT NULL;
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"fun_article_id":', NEW.fun_article_id, ''));
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"src":', NEW.src, ''));
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"article_type":', NEW.article_type, ''));
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"is_valid":', NEW.is_valid, ''));
INSERT IGNORE INTO t_fun_cron_queue(`source`, `op`, `key`, `value`)
VALUES('t_fun_article_filter', 'update', CONCAT('{"id":', NEW.id, '}'),
    CONCAT('{"after":{"filterInfo":{', after_vals, '}}}'));
END
              Timing: AFTER
             Created: NULL
            sql_mode: 
             Definer: funuser@%
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
*************************** 7. row ***************************
             Trigger: fun_article_filter_delete
               Event: DELETE
               Table: t_fun_article_filter
           Statement: BEGIN
DECLARE after_vals VARCHAR(1023) DEFAULT NULL;
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"fun_article_id":', OLD.fun_article_id, ''));
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"src":', OLD.src, ''));
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"article_type":', OLD.article_type, ''));
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"is_valid":', 0, ''));
INSERT IGNORE INTO t_fun_cron_queue(`source`, `op`, `key`, `value`)
VALUES('t_fun_article_filter', 'delete', CONCAT('{"id":', OLD.id, '}'),
    CONCAT('{"after":{"filterInfo":{', after_vals, '}}}'));
END
              Timing: AFTER
             Created: NULL
            sql_mode: 
             Definer: funuser@%
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
*************************** 8. row ***************************
             Trigger: fun_user_delete
               Event: DELETE
               Table: t_fun_user
           Statement: BEGIN
DECLARE var_fun_article_id bigint(20) default 0;
DECLARE done INT DEFAULT FALSE;
DECLARE curFunTable CURSOR FOR select fun_article_id from t_fun_article where fun_user_id = OLD.fun_user_id;
DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
OPEN curFunTable;
cron_queue_insert_loop : LOOP
FETCH curFunTable INTO var_fun_article_id;
IF done THEN
    LEAVE cron_queue_insert_loop;
END IF;
INSERT IGNORE INTO t_fun_cron_queue(source, op, `key`) VALUES('t_fun_article', 'delete', 
    CONCAT('{"fun_article_id":', var_fun_article_id, '}'));
END LOOP;
CLOSE curFunTable;
  END
              Timing: BEFORE
             Created: NULL
            sql_mode: 
             Definer: funuser@%
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
*************************** 9. row ***************************
             Trigger: fun_article_update
               Event: UPDATE
               Table: t_fun_article
           Statement: BEGIN
DECLARE userInfo VARCHAR(767) DEFAULT NULL;
DECLARE articleInfo VARCHAR(767) DEFAULT NULL;
DECLARE owner_name VARCHAR(128);
DECLARE owner_icon VARCHAR(256);
DECLARE owner_type int(3);
DECLARE is_finish_insert int (3) DEFAULT 0;

IF NEW.is_show_content_ready = 1 THEN

    IF NEW.is_finish <> OLD.is_finish AND OLD.is_finish = 0 THEN
        SET is_finish_insert = 1;
    END IF;
    IF is_finish_insert = 1 OR NEW.fun_user_id <> OLD.fun_user_id THEN

        select name, icon, type into owner_name, owner_icon, owner_type from t_fun_user where fun_user_id = NEW.fun_user_id;
        SET userInfo = CONCAT_WS(',', userInfo, CONCAT('"user_id":"', REPLACE(NEW.fun_user_id, '"', '"'), '"'));
        SET userInfo = CONCAT_WS(',', userInfo, CONCAT('"user_type":', REPLACE(owner_type, '"', '"'), ''));
        SET userInfo = CONCAT_WS(',', userInfo, CONCAT('"user_name":"', REPLACE(owner_name, '"', '"'), '"'));
        SET userInfo = CONCAT_WS(',', userInfo, CONCAT('"user_icon":"', REPLACE(owner_icon, '"', '"'), '"'));
    END IF;

    IF is_finish_insert = 1 OR NEW.is_show_content_ready <> OLD.is_show_content_ready 
        OR NEW.article_title <> OLD.article_title OR NEW.article_desc <> OLD.article_desc
        OR NEW.src <> OLD.src OR NEW.article_type <> OLD.article_type THEN
        SET articleInfo = CONCAT_WS(',', articleInfo, CONCAT('"article_title":"',REPLACE(NEW.article_title, '"', '"'), '"'));
        SET articleInfo = CONCAT_WS(',', articleInfo, CONCAT('"article_desc":"',REPLACE(NEW.article_desc, '"', '"'), '"'));
        SET articleInfo = CONCAT_WS(',', articleInfo, CONCAT('"update_time":"',REPLACE(NEW.update_time, '"', '"'), '"'));
        SET articleInfo = CONCAT_WS(',', articleInfo, CONCAT('"src":', REPLACE(NEW.src, '"', '"'), ''));
        SET articleInfo = CONCAT_WS(',', articleInfo, CONCAT('"article_type":', REPLACE(NEW.article_type, '"', '"'), ''));
        SET articleInfo = CONCAT_WS(',', articleInfo, CONCAT('"article_url":"',REPLACE(NEW.article_url, '"', '"'), '"'));
    END IF;

    IF is_finish_insert = 1 THEN
        INSERT IGNORE INTO t_fun_cron_queue(source, op, `key`, value) VALUES('t_fun_article', 'insert', 
            CONCAT('{"fun_article_id":', NEW.fun_article_id, '}'), 
            CONCAT('{"userInfo":{', userInfo, '},"articleInfo":{', articleInfo, '}}'));
    ELSEIF userInfo <> '' AND articleInfo <> '' THEN
        INSERT IGNORE INTO t_fun_cron_queue(source, op, `key`, value) VALUES('t_fun_article', 'update', 
            CONCAT('{"fun_article_id":', NEW.fun_article_id, '}'), 
            CONCAT('{"after":{"userInfo":{', userInfo, '},"articleInfo":{', articleInfo, '}}}'));
    ELSEIF userInfo <> '' THEN
        INSERT IGNORE INTO t_fun_cron_queue(source, op, `key`, value) VALUES('t_fun_article', 'update', 
            CONCAT('{"fun_article_id":', NEW.fun_article_id, '}'),
            CONCAT('{"after":{"userInfo":{', userInfo, '}}}'));
    ELSEIF articleInfo <> '' THEN
        INSERT IGNORE INTO t_fun_cron_queue(source, op, `key`, value) VALUES('t_fun_article', 'update', 
            CONCAT('{"fun_article_id":', NEW.fun_article_id, '}'),
            CONCAT('{"after":{"articleInfo":{', articleInfo, '}}}'));
    END IF;
END IF;
END
              Timing: AFTER
             Created: NULL
            sql_mode: 
             Definer: funuser@%
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
*************************** 10. row ***************************
             Trigger: fun_owner_update
               Event: UPDATE
               Table: t_fun_owner
           Statement: BEGIN
DECLARE after_vals VARCHAR(65535) DEFAULT NULL;

DECLARE fun_id int(11) default 0;

DECLARE done INT DEFAULT FALSE;

DECLARE curFunTable CURSOR FOR select id from t_fun where fun_owner_id = NEW.id;

DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;


IF NEW.type <> OLD.type THEN
    SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"user_type":', REPLACE(NEW.type, '"', '"'), ''));
END IF;

IF NEW.name <> OLD.name THEN
    SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"user_name":"', REPLACE(NEW.name, '"', '"'), '"'));
END IF;

IF NEW.icon <> OLD.icon THEN
    SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"user_icon":"', REPLACE(NEW.icon, '"', '"'), '"'));
END IF;

IF after_vals <> '' THEN
    OPEN curFunTable;
    cron_queue_insert_loop : LOOP
    FETCH curFunTable INTO fun_id;
    IF done THEN
        LEAVE cron_queue_insert_loop;
    END IF;
    INSERT IGNORE INTO t_fun_cron_queue(source, op, `key`, value) VALUES('t_fun', 'update', CONCAT('{"fun_id":', fun_id, '}'),CONCAT('{"after":{', after_vals, '}}'));
END LOOP;
CLOSE curFunTable;
END IF;
  END
              Timing: AFTER
             Created: NULL
            sql_mode: 
             Definer: funuser@%
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
*************************** 11. row ***************************
             Trigger: fun_user_update
               Event: UPDATE
               Table: t_fun_user
           Statement: BEGIN
DECLARE userInfo VARCHAR(65535) DEFAULT NULL;

DECLARE var_fun_article_id bigint(20) default 0;

DECLARE done INT DEFAULT FALSE;

DECLARE curFunTable CURSOR FOR select fun_article_id from t_fun_article where fun_user_id = NEW.fun_user_id;

DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

SET userInfo = CONCAT_WS(',', userInfo, CONCAT('"user_id":"', REPLACE(NEW.fun_user_id, '"', '"'), '"'));
SET userInfo = CONCAT_WS(',', userInfo, CONCAT('"user_type":', REPLACE(NEW.type, '"', '"'), ''));
SET userInfo = CONCAT_WS(',', userInfo, CONCAT('"user_name":"', REPLACE(NEW.name, '"', '"'), '"'));
SET userInfo = CONCAT_WS(',', userInfo, CONCAT('"user_icon":"', REPLACE(NEW.icon, '"', '"'), '"'));

IF userInfo <> '' THEN
    OPEN curFunTable;
    cron_queue_insert_loop : LOOP
    FETCH curFunTable INTO var_fun_article_id;
    IF done THEN
        LEAVE cron_queue_insert_loop;
    END IF;
    INSERT IGNORE INTO t_fun_cron_queue(source, op, `key`, value) VALUES('t_fun_article', 'update', 
        CONCAT('{"fun_article_id":', var_fun_article_id, '}'),
        CONCAT('{"after":{"userInfo":{', userInfo, '}}}'));
END LOOP;
CLOSE curFunTable;
END IF;
  END
              Timing: AFTER
             Created: NULL
            sql_mode: 
             Definer: funuser@%
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
