drop table Marks, GroupCourse;
drop table Groups, Students, Courses, Lecturers;

create table Groups (
  id int not null,
  name varchar(50) not null
);
create table Students (
  id int not null,
  name varchar(50) not null,
  group_id int not null
);
create table Courses (
  id int not null,
  name varchar(50) not null
);
create table Lecturers (
  id int not null,
  name varchar(50) not null
);
create table Marks (
  value int null,
  student_id int not null,
  course_id int not null
);
create table GroupCourse (
  group_id int not null,
  course_id int not null,
  lecturer_id int null
);

alter table Groups add primary key (id);
alter table Students add primary key (id);
alter table Courses add primary key (id);
alter table Lecturers add primary key (id);
alter table Marks add primary key (student_id, course_id);
alter table GroupCourse add primary key (group_id, course_id);

alter table Students add foreign key (group_id) references Groups(id);

alter table Marks add foreign key (student_id) references Students(id);
alter table Marks add foreign key (course_id) references Courses(id);

alter table GroupCourse add foreign key (group_id) references Groups(id);
alter table GroupCourse add foreign key (course_id) references Courses(id);
alter table GroupCourse add foreign key (lecturer_id) references Lecturers(id);

insert into Groups
  (id, name) values
  (1, 'M3435'),
  (2, 'M3436'),
  (3, 'M3437'),
  (4, 'M3439');

insert into Students
  (id, name, group_id) values
  (1, 'Nursan Valeyev', 3),
  (2, 'Someone Someone', 1);

insert into Courses
  (id, name) values
  (1, 'dbms');

insert into Lecturers
  (id, name) values
  (1, 'Georgiy Korneev');

insert into GroupCourse
  (group_id, course_id, lecturer_id) values
  (1, 1, 1),
  (3, 1, 1);

insert into Marks
  (student_id, course_id, value) values
  (1, 1, 5),
  (2, 1, 4);

select Students.name, Groups.name
    from Students
      inner join Groups on Students.group_id = Groups.id;
select Lecturers.name, Courses.name, Groups.name
    from Lecturers
      inner join GroupCourse on Lecturers.id = GroupCourse.lecturer_id
      inner join Courses on GroupCourse.course_id = Courses.id
      inner join Groups on GroupCourse.group_id = Groups.id;
select Students.name, Courses.name, Marks.value, Lecturers.name
    from Marks
      inner join Students on Students.id = Marks.student_id
      inner join Courses on Courses.id = Marks.course_id
      inner join GroupCourse on GroupCourse.course_id = Courses.id and GroupCourse.group_id = Students.group_id
      inner join Lecturers on Lecturers.id = GroupCourse.lecturer_id;
