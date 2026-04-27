--  --------id相同，执行顺序由上至下-------------
explain
select 
		c.class_name, st.student_name 
from class c 
inner join student st on c.id = st.id 
where st.student_name='林冲';

explain
select 
		c.class_name, st.student_name 
from student st
inner join  class c  on  st.id = c.id
where st.student_name='林冲';

-- -------------------------------------------------
explain select 
		c.class_name, st.student_name 
from class c 
inner join student st on c.id = st.id 
where c.class_name='一班';



--  ---------------id不同, id值越大，优先级越高，越先被执行
explain
select * from student where id = (
select id from class where class_name = '一班'
);

-- -------------------------------------------
explain
select * from  class  where id = (
select id from student where student_name = '武松'
);

-- id既有相同又有不同，不同的id值，id值越大，优先级越高，越先被执行; 
-- 相同的id值，按照从上到下的顺序执行
explain
select * from student s
inner join equip e on e.id = s.id
where s.id = (
select id from class where class_name = '一班'
);


-- -----------2select_type字段-----------
explain SELECT * FROM student;

explain SELECT * FROM equip
UNION
select * from script;

explain
select  e.* from student s
inner join equip e on e.id = s.id
where s.id = (
select id from class c where class_name = '一班'
)
union
select  e2.* from student s2
inner join equip e2 on e2.id = s2.id
where s2.id = (
select id from class c2 where class_name = '二班'
)

-- ----------------------3table字段------------------
explain
select  e.* from student s
inner join equip e on e.id = s.id
where s.id = (
select id from class c where class_name = '一班'
)
union
select  e2.* from student s2
inner join equip e2 on e2.id = s2.id
where s2.id = (
select id from class c2 where class_name = '二班'
)

-- -----------4 type字段--------------------------------
explain
select * from  student st where id =1;

explain
select * from  student st
inner join class c on c.id = st.id
where st.id>5; 


explain
select * from  student st where student_name = '武松'

explain
select * from  student st where mobile = '15638204123';


-- -----------5、key_len的大小------
-- student_name: 设置了非主键索引
explain
select * from  student st where student_name = '武松'


--   ------------------6、rows---------------
explain
select * from  student st
inner join class c on c.id = st.id



-- -----------7fliters-------
explain
select * from  student st
inner join class c on c.id = st.id
where st.id>5  and class_name = '三班';

-- -----------------8Extra-------------------------
-- using filesort
explain
select * from student order by mobile;

-- ----------------using TEMPORARY
explain
select *  from (
		select count(*) as num from student group by nick_name 
) temp 
where temp.num>3;


-- student_name是非主键索引
-- using index
explain
select id as num from student  where student_name = '武松';


-- -------using where
explain
select id as num from student  where nick_name = '哩哩2';

-- impossible where
explain
select id as num from student  where 1 = 2;

