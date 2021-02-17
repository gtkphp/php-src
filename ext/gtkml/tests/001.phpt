--TEST--
Check for gtkml presence
--SKIPIF--
<?php if (!extension_loaded("gtkml")) print "skip"; ?>
--FILE--
<?php
echo "gtkml extension is available";

?>
--EXPECT--
gtkml extension is available
