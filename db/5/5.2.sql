select StudentName, CourseName from Students natural join Plan natural join Courses except select StudentName, CourseName from Students natural join Plan natural join Courses natural join Marks
