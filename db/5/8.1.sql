select cast(sum(Mark) as float) / cast(count(*) as float) as AvgMark from Marks where StudentId = :StudentId
