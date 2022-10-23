drop table Teachers, CourseTeacher, Marks, GroupStudent;
drop table Groups, Students, Courses;

create table Groups (
  id int not null,
  name varchar(50) not null
);
create table Students (
  id int not null,
  first_name varchar(50) not null,
  last_name varchar(50) not null
);
create table Marks (
  student_id int not null,
  course_id int not null,
  value int null
);
create table Courses (
  id int not null,
  name varchar(50) not null
);
create table Teachers (
  id int not null,
  first_name varchar(50) not null,
  last_name varchar(50) not null,
  course_id int null
);
create table GroupStudent (
  group_id int not null,
  student_id int not null
);
create table CourseTeacher (
  course_id int not null,
  teacher_id int not null
);

alter table Groups add primary key (id);
alter table Students add primary key (id);
alter table Courses add primary key (id);
alter table Teachers add primary key (id);
alter table GroupStudent add primary key (student_id);
alter table CourseTeacher add primary key (course_id, teacher_id);
alter table Marks add primary key (student_id, course_id);

alter table GroupStudent add foreign key (group_id) references Groups(id);
alter table GroupStudent add foreign key (student_id) references Students(id);

alter table CourseTeacher add foreign key (course_id) references Courses(id);
alter table CourseTeacher add foreign key (teacher_id) references Teachers(id);
alter table Teachers add foreign key (id, course_id) references CourseTeacher(teacher_id, course_id);

alter table Marks add foreign key (student_id) references Students(id);
alter table Marks add foreign key (course_id) references Courses(id);

insert into Groups
  (id, name) values
  (1, 'M3435'),
  (2, 'M3436'),
  (3, 'M3437'),
  (4, 'M3439');

insert into Students
  (id, first_name, last_name) values
  (1, 'Nursan', 'Valeyev'),
  (2, 'Someone', 'Someone');

insert into Courses
  (id, name) values
  (1, 'dbms');

insert into Teachers
  (id, first_name, last_name) values
  (1, 'Georgiy', 'Korneev');

insert into GroupStudent
  (group_id, student_id) values
  (1, 2),
  (3, 1);

insert into CourseTeacher
  (course_id, teacher_id) values
  (1, 1);

insert into Marks
  (student_id, course_id, value) values
  (1, 1, 5),
  (2, 1, 4);

select Students.last_name, Groups.name
    from Students
      inner join GroupStudent on Students.id = GroupStudent.student_id
      inner join Groups on GroupStudent.group_id = Groups.id;
select Teachers.last_name, Courses.name
    from Teachers
      inner join CourseTeacher on Teachers.id = CourseTeacher.teacher_id
      inner join Courses on CourseTeacher.course_id = Courses.id;
select Students.last_name, Courses.name, Marks.value, Teachers.last_name
    from Students
      inner join Marks on Students.id = Marks.student_id
      inner join Courses on Marks.course_id = Courses.id
      inner join CourseTeacher on Courses.id = CourseTeacher.course_id
      inner join Teachers on CourseTeacher.teacher_id = Teachers.id;
