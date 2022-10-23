drop table if exists Marks CASCADE;
drop table if exists Plan CASCADE;
drop table if exists Students CASCADE;
drop table if exists Groups CASCADE;
drop table if exists Courses CASCADE;
drop table if exists Lecturers CASCADE;
drop function if exists update_mark;
drop function if exists update_losers;

CREATE TABLE Groups(
  GroupId   int     not null primary key,
  GroupName char(5) not null unique
);

CREATE TABLE Students
(
  StudentId   int  not null primary key,
  StudentName varchar(50) not null,
  GroupId     int  not null,
  foreign key (GroupId) references Groups (GroupId)
);

CREATE TABLE Courses
(
  CourseId   int  not null primary key,
  CourseName varchar(50) not nulL
);

CREATE TABLE Lecturers
(
  LecturerId   int  not null primary key,
  LecturerName varchar(50) not nulL
);

CREATE TABLE Marks
(
  StudentId int not null,
  CourseId  int not null,
  Mark      int not null,
  primary key (StudentId, CourseId),
  foreign key (CourseId) references Courses (CourseId),
  foreign key (StudentId) references Students (StudentId)
  on delete cascade
);

CREATE TABLE Plan
(
  CourseId   int not null,
  GroupId    int not null,
  LecturerId int not null,
  PRIMARY KEY (CourseId, GroupId),
  FOREIGN KEY (CourseId) REFERENCES Courses (CourseId),
  FOREIGN KEY (GroupId) REFERENCES Groups (GroupId),
  FOREIGN KEY (LecturerId) REFERENCES Lecturers (LecturerId)
);

INSERT INTO Groups(GroupId, GroupName)
VALUES (1, 'M3435'),
       (2, 'M3437'),
       (3, 'M3439'),
       (4, 'M3438');

INSERT INTO Students (StudentId, StudentName, GroupId)
VALUES (1, 'Илья Кокорин', 3),
       (2, 'Лев Довжик', 3),
       (3, 'Артём Абрамов', 3),
       (4, 'Николай Рыкунов', 1),
       (5, 'Ярослав Балашов', 1),
       (6, 'Никита Дугинец', 2);

INSERT INTO Courses(CourseId, CourseName)
VALUES (1, 'Математический анализ'),
       (2, 'Технологии Java'),
       (3, 'Базы данных'),
       (4, 'Теория вероятностей'),
       (5, 'Матстат');

INSERT INTO Lecturers (LecturerId, LecturerName)
VALUES (1, 'Георгий Корнеев'),
       (2, 'Константин Кохась'),
       (3, 'Ольга Семёнова'),
       (4, 'Ирина Суслина');

INSERT INTO Plan (CourseId, GroupId, LecturerId)
VALUES (1, 1, 3),
       (1, 2, 3),
       (1, 3, 2),
       (2, 2, 1),
       (2, 3, 1),
       (3, 3, 1),
       (4, 3, 4),
       (5, 3, 4);


INSERT INTO Marks (StudentId, CourseId, Mark)
VALUES (1, 1, 100),
       (1, 2, 85),
       (1, 3, 75),
       (2, 1, 75),
       (2, 2, 85),
       (2, 3, 100),
       (4, 1, 100),
       (5, 1, 75),
       (6, 1, 100),
       (6, 2, 85),
       (1, 4, 100),
       (2, 5, 85),
       (1, 5, 50);
