#gd_sqliteTest.gd


static func RunTest():
	var SQL_OK = 101
	randomize();
	
	print("Start GDSqlite test.")
	var timer = OS.get_ticks_msec();
	# disk db test
	var GDSqlite = preload('res://lib/gd_sqlite.gdns');
	var db = GDSqlite.new();
	print('Open db');
	if db.open('test.sql') != 0:
		print(db.get_error());
	print(db.get_path());
	print('Create table');
	if(db.create_table('test', ['id INTEGER PRIMARY KEY DEFAULT NULL', 'name TEXT', 'test INTEGER']) != SQL_OK):
		print(db.get_error());
	print('Insert query');
	if( db.query('INSERT INTO test (name, test) VALUES ("test", "%d");' % ( randi() % 1000 + 1 )) != SQL_OK):
		print(db.get_error());
	var data = db.query_array('SELECT * FROM test;');
	print(data.size());
	for item in data:
		for key in item.keys():
			print(item[key]);
	print('Close db: %d' % db.close());
	print(OS.get_ticks_msec() - timer);
	
	# in memory db test
	var memdb = GDSqlite.new();
	print('Open in-memory db: %d' % memdb.open('memtest.sql', true));
	print('Create table: %d' % memdb.create_table('test', ['id INTEGER PRIMARY KEY DEFAULT NULL', 'name TEXT', 'test INTEGER']));
	print('Insert query: %d' % memdb.query('INSERT INTO test (name, test) VALUES ("test", "%d");' % (randi() % 1000 + 1)));
	data = memdb.query_array('SELECT * FROM test;');
	print(data.size());
	for item in data:
		for key in item.keys():
			print(item[key]);
	print('Save db: %d' % memdb.save());
	print('Close db: %d' % memdb.close());
	print(OS.get_ticks_msec() - timer);