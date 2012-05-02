use <ninevolt.scad>

$fn=20;

dark = [0.4,0.4,0.4];

module board()
{
	difference()
	{
	translate([0,-2,0])
	cube([36,97,1]);
	holes();
	}
}


module rotary()
{
	color([0.5,1,0.5])
	translate([0,0,3])
	cube([13,13,6],true);
	color(dark)
	cylinder(r=3, h=17);		
}

module led()
{
	translate([0,0,10]) color([.9,0,0])
	{
		cylinder(r=3.0,h=1);
		cylinder(r=2.5,h=4);
		translate([0,0,4])
		sphere(r=2.5);
	}
	
	color(dark) translate([0,1.25,0])
	{
		cylinder(r=.2,h=10);
	}
	
	color(dark) translate([0,-1.25,0])
	{
		cylinder(r=.2,h=10);
	}
}

module holes()
{
	
	{
		translate([3,3,-1])
		cylinder(r=1, h=30);
		translate([33,3,-1])
		cylinder(r=1, h=30);
		translate([3,78,-1])
		cylinder(r=1, h=30);
		translate([33,78,-1])
		cylinder(r=1, h=30);
	}
}

module screen()
{
	translate([0,0,10])
	{
		difference()
		{
			color([0,.9,.1])
			cube([35,80,1]);

			holes();
		}
		color(dark)
		translate([5,5,0])
		cube([27,71,10]);
		
		color([0,0,0])
		translate([8,7.5,6])
		cube([20,65,5]);
		

	}	
}

module speaker()
{
	difference()
	{
	color(dark)
	cylinder(r=5.75, h=8);
	cylinder(r=1, h=8);
	}
}

module usb()
{
	color([.8,.8,0])
	translate([0,0,2.8])
	rotate([90,0,90])
	import(file="usbJack_B.stl");
}


module dc_jack()
{
	translate([0,0,8])
	rotate([90,0,0])
	color(dark)
	import(file="pj-019.stl");
}



module switch()
{
	rotate([90,0,90])
	color(dark)
	import(file="surfaceswitch.stl");
}

module connector()
{
	color([0,0,0])
	rotate([0,0,90])
	cube([41,2,12]);
}

module components()
{
	translate([-36,0,0]) board();
	translate([-8.8,89,0]) rotary();
	translate([-21.5,92,]) led();
	translate([-30.386,88.6612,0]) speaker();
	translate([-36,0,2.5]) screen();
	translate([-68,40,0]) rotate ([0,0,0])  ninevolt();
	translate([1,71.628,0]) usb();
	translate([-1.4,11,1]) switch();
	translate([5,25,0])dc_jack();
	translate([-32,10,1])connector();
	
}




translate([-36,-20,0])
rotate([00,00,-90])
{	
	components();
}

