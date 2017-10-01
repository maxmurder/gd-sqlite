extends Node

var GDSqlite = load("res://lib/gd_sqlite.gdns");
var db = GDSqlite.new();

func _ready():
	db.open("test.sql");
	print(db.get_path());
	print(db.create_table("test", ["id INTEGER PRIMARY KEY AUTOINCREMENT", "name TEXT", "test INTEGER"]));
	print(db.query("INSERT INTO test (name, test) VALUES ('test', '420');"));
	var data = db.query_array("SELECT * FROM test;");
	print(data.size());
	for item in data:
		for key in item.keys():
			print(item[key]);
	print(db.close());
	get_tree().quit();
	pass