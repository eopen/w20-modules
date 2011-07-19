<?php 
global $base_url, $base_path;
?>

<script src="http://maps.google.com/maps?file=api&amp;v=2.x&amp;key=ABQIAAAA1memWu18TVsLI4EKOmBrbRSQugB6jzsNCP0Q864fXfa8fCpQCRQyRw9daquHZVPJCjIZ0jROdokDiQ" type="text/javascript"></script>

<div id="map" style="width: 100%; height: 600px"></div>
	
<SCRIPT LANGUAGE="JavaScript">

	function createMarker(point,html) {
        var marker = new GMarker(point, markerOptions);
        GEvent.addListener(marker, "click", function() {
          marker.openInfoWindowHtml(html);
        });
        return marker;
    }
	  
	var map = new GMap2(document.getElementById("map"));
	map.addControl(new GLargeMapControl());
	map.addControl(new GMapTypeControl());
	map.addControl(new GOverviewMapControl());
	map.enableScrollWheelZoom();
   	map.enableDoubleClickZoom();
	map.setCenter(new GLatLng(-23.673,-46.651), 10);
		
	var Icon = new GIcon(G_DEFAULT_ICON);
	var size = iconData[iname];
	Icon.shadow = null;
	Icon.iconSize = new GSize(size.width, size.height);
	Icon.iconAnchor = new GPoint(size.width >> 1, size.height >> 1);
	markerOptions = { icon:Icon, draggable:false};
	
	var point = new GLatLng(array4[0],array4[1]);
	var marker = createMarker(point," ");
	map.addOverlay(marker);
	
</script>
	