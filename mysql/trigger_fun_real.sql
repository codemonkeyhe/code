delimiter |   
drop trigger if exists fun_article_update
|
create trigger  fun_article_update
AFTER UPDATE
on  t_fun_article
for each row  BEGIN
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
        SET userInfo = CONCAT_WS(',', userInfo, CONCAT('"user_id":"', REPLACE(NEW.fun_user_id, '"', '\"'), '"'));
        SET userInfo = CONCAT_WS(',', userInfo, CONCAT('"user_type":', REPLACE(owner_type, '"', '\"'), ''));
        SET userInfo = CONCAT_WS(',', userInfo, CONCAT('"user_name":"', REPLACE(owner_name, '"', '\"'), '"'));
        SET userInfo = CONCAT_WS(',', userInfo, CONCAT('"user_icon":"', REPLACE(owner_icon, '"', '\"'), '"'));
    END IF;

    IF is_finish_insert = 1 OR NEW.is_show_content_ready <> OLD.is_show_content_ready 
        OR NEW.article_title <> OLD.article_title OR NEW.article_desc <> OLD.article_desc
        OR NEW.src <> OLD.src OR NEW.article_type <> OLD.article_type THEN
        SET articleInfo = CONCAT_WS(',', articleInfo, CONCAT('"article_title":"',REPLACE(NEW.article_title, '"', '\"'), '"'));
        SET articleInfo = CONCAT_WS(',', articleInfo, CONCAT('"article_desc":"',REPLACE(NEW.article_desc, '"', '\"'), '"'));
        SET articleInfo = CONCAT_WS(',', articleInfo, CONCAT('"update_time":"',REPLACE(NEW.update_time, '"', '\"'), '"'));
        SET articleInfo = CONCAT_WS(',', articleInfo, CONCAT('"src":', REPLACE(NEW.src, '"', '\"'), ''));
        SET articleInfo = CONCAT_WS(',', articleInfo, CONCAT('"article_type":', REPLACE(NEW.article_type, '"', '\"'), ''));
        SET articleInfo = CONCAT_WS(',', articleInfo, CONCAT('"article_url":"',REPLACE(NEW.article_url, '"', '\"'), '"'));
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
 |   


drop trigger if exists fun_article_delete
| 
create trigger  fun_article_delete
AFTER DELETE
on  t_fun_article
for each row  BEGIN
INSERT IGNORE INTO t_fun_cron_queue(source, op, `key`)
VALUES('t_fun_article', 'delete', CONCAT('{"fun_article_id":', OLD.fun_article_id, '}'));
END
 |   

drop trigger if exists fun_article_filter_insert
| 
create trigger  fun_article_filter_insert
AFTER INSERT
on  t_fun_article_filter
for each row  BEGIN
DECLARE after_vals VARCHAR(1023) DEFAULT NULL;
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"fun_article_id":', NEW.fun_article_id, ''));
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"src":', NEW.src, ''));
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"article_type":', NEW.article_type, ''));
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"is_valid":', NEW.is_valid, ''));
INSERT IGNORE INTO t_fun_cron_queue(`source`, `op`, `key`, `value`)
VALUES('t_fun_article_filter', 'insert', CONCAT('{"id":', NEW.id, '}'),
    CONCAT('{"after":{"filterInfo":{', after_vals, '}}}'));
END
 |   

drop trigger if exists fun_article_filter_update
| 
create trigger  fun_article_filter_update
AFTER UPDATE
on  t_fun_article_filter
for each row  BEGIN
DECLARE after_vals VARCHAR(1023) DEFAULT NULL;
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"fun_article_id":', NEW.fun_article_id, ''));
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"src":', NEW.src, ''));
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"article_type":', NEW.article_type, ''));
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"is_valid":', NEW.is_valid, ''));
INSERT IGNORE INTO t_fun_cron_queue(`source`, `op`, `key`, `value`)
VALUES('t_fun_article_filter', 'update', CONCAT('{"id":', NEW.id, '}'),
    CONCAT('{"after":{"filterInfo":{', after_vals, '}}}'));
END
 |   

drop trigger if exists fun_article_filter_delete
| 
create trigger  fun_article_filter_delete
AFTER DELETE
on  t_fun_article_filter
for each row  BEGIN
DECLARE after_vals VARCHAR(1023) DEFAULT NULL;
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"fun_article_id":', OLD.fun_article_id, ''));
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"src":', OLD.src, ''));
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"article_type":', OLD.article_type, ''));
SET after_vals = CONCAT_WS(',', after_vals, CONCAT('"is_valid":', 0, ''));
INSERT IGNORE INTO t_fun_cron_queue(`source`, `op`, `key`, `value`)
VALUES('t_fun_article_filter', 'delete', CONCAT('{"id":', OLD.id, '}'),
    CONCAT('{"after":{"filterInfo":{', after_vals, '}}}'));
END
 |   


drop trigger if exists fun_user_update 
| 
create trigger  fun_user_update
AFTER UPDATE
on  t_fun_user
for each row  BEGIN
DECLARE userInfo VARCHAR(65535) DEFAULT NULL;

DECLARE var_fun_article_id bigint(20) default 0;

DECLARE done INT DEFAULT FALSE;

DECLARE curFunTable CURSOR FOR select fun_article_id from t_fun_article where fun_user_id = NEW.fun_user_id;

DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

SET userInfo = CONCAT_WS(',', userInfo, CONCAT('"user_id":"', REPLACE(NEW.fun_user_id, '"', '\"'), '"'));
SET userInfo = CONCAT_WS(',', userInfo, CONCAT('"user_type":', REPLACE(NEW.type, '"', '\"'), ''));
SET userInfo = CONCAT_WS(',', userInfo, CONCAT('"user_name":"', REPLACE(NEW.name, '"', '\"'), '"'));
SET userInfo = CONCAT_WS(',', userInfo, CONCAT('"user_icon":"', REPLACE(NEW.icon, '"', '\"'), '"'));

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
 |   

drop trigger if exists fun_user_delete
| 
create trigger  fun_user_delete
BEFORE DELETE
on  t_fun_user
for each row  BEGIN
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
|
delimiter ;
