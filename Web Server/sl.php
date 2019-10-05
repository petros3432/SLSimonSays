<?php

if(isset($_GET["test"]))
{
	echo $_GET["test"];
	file_put_contents("TEST.txt", $_GET["test"]);
} 
