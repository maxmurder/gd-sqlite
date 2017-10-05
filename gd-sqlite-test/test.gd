extends Node

var TestScript = load("res://gd_sqliteTest.gd");
#var ts = TestScript.new() 

func _ready():
	TestScript.RunTest();
	get_tree().quit();
	pass