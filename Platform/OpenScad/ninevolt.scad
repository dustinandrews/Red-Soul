$fn=20;
module ninevolt()
{
          color([0.4,0.4,0.4,1])
          cube([26,44,17]);	
	color([0.8,0.8,0.9,1])
	{
					
		translate([5,1,8.5]) rotate([-90,0,0])
				cylinder(r=3,h=46.5);			
		translate([19,1,8.5]) rotate([-90,0,0])
			cylinder(r=4,h=46.5, $fn=6);		
	}
}

ninevolt();