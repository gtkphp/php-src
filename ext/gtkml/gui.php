<?php
/**
<?xml version="1.0"?>
<?xml-php version=">=7.2.*"?>
<!DOCTYPE window PUBLIC "-//GTK//DTD GTKML 1.0//EN"
  "http://www.gtk.org/Builder/GTKML/1.1/DTD/gtkml.dtd">
   http://www.gtk.org/TR/gtkml1/DTD/gtkml1-strict.dtd
class MyWindow extends Gtk\Window {
    public function __construct() {
        parent::__construct(Gtk\WindowType::TOPLEVEL);
        $this->setTitle("My Window");
    }
    public function build_ui() {
        $this->add(new Gtk\Label("Hello World"));
    }
}

GTKMLDocument::registerNodeClass("window", MyWindow);
...

*/

/*
<window>
  <script type="text/php"><?cdata  // hack to got higlight
    echo "Hello World";
  ?></script>
  <form>
    <label>Field</label> : <input type="radio" value="" />
  <form>
</window>

<label for="male">Male</label>
<input type="radio" name="gender" id="male" value="male"><br>
<label for="female">Female</label>
<input type="radio" name="gender" id="female" value="female"><br>
<label for="other">Other</label>
<input type="radio" name="gender" id="other" value="other"><br><br>
<input type="submit" value="Submit">
<label></label>
*/

?><window>
  <?php echo "Hello World !"?>
</window>
