pi {GroupId, CourseId} (pi{CourseId, StudentId} (sigma{Mark ≠ null && Mark >= 3} (Students njoin Marks)) gdiv pi {StudentId, GroupId} (Students))
