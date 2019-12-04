# mysql-utf8-fix
converter from mysql-double-utf8 to regular utf8

# Usage

compile with gcc

then use it with your SQL dump like this

./a.out my-sql-dump.sql new-sql-dump.sql

you will end up with a SQL dump that has proper utf8 encoding. Import that dump into your database and you're done.

# Attention

in some configurations mysqldump will put localized comments in your original dump. better remove all SQL comments (lines starting with --) before converting.

