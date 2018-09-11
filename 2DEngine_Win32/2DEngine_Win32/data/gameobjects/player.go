<?xml version="1.0" encoding="UTF-8" ?>
<gob>
	<resources>
		<renderable type="Renderable" name="Walk1" pivotpoint="center" texleft="0.933430" texright="0.963821" texbottom="0.00289" textop="0.033237" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="Walk2" pivotpoint="center" texleft="0.966715" texright="0.997106" texbottom="0.00289" textop="0.033237" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
		
	</resources>
	<gameobject type="Player" name="Player" walkacceleration=".15" maxwalkspeed="4." runacceleration=".25" maxrunspeed="6." jumppower="8.0" >
		<transform x="7" y="7" z=".5" rotation="0" sx="1" sy="1" sz="1" />
		<components>
			<rigidbody type="Rigidbody" bodytype="dynamic" canrotate="false" >
				<boxcollider type="Box" name="PlayerTopCollider" width=".8" height=".85" xrel="0.0" yrel=".25" angle="0.0" density="1.0" friction=".3" issensor="false" />
				<boxcollider type="Box" name="HeadSensor" width=".6" height=".85" xrel="0.0" yrel=".3" angle="0.0" density="1.0" friction=".3" issensor="true" />
				<boxcollider type="Box" name="GroundSensor" width=".5" height=".5" xrel="0.0" yrel="-.675" angle="0.0" density="1.0" friction=".3" issensor="true" />
				<circlecollider type="Circle" name="PlayerBottomCollider" radius=".45" xrel="0.0" yrel="-.175" density="1.0" friction=".3" issensor="false" />
			</rigidbody>
			<animator type="Animator" startinganimation="0">
				<animation name="Walk" frameinterval=".03" islooping="false">
					<sprite type="Sprite" name="Walk1" renderablename="Walk1" renderorder="4" isrendered="false" width="1" height="1.35" xrel="0" yrel="0" />
					<sprite type="Sprite" name="Walk2" renderablename="Walk2" renderorder="4" isrendered="false" width="1" height="1.35" xrel="0" yrel="0" />
				</animation>
				
			</animator>
		</components>
	</gameobject>
</gob>