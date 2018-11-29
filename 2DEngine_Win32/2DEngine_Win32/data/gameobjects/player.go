<?xml version="1.0" encoding="UTF-8" ?>
<gob>
	<resources>
		<renderable type="Renderable" name="GreenAlienFace" pivotpoint="center" texleft="0.634393" texright="0.664739" texbottom="0.00289" textop="0.033237" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="GreenAlienJump1" pivotpoint="center" texleft="0.667630" texright="0.697976" texbottom="0.00289" textop="0.033237" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
		<renderable type="Renderable" name="GreenAlienJump2" pivotpoint="center" texleft="0.700867" texright="0.731213" texbottom="0.00289" textop="0.033237" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
		<renderable type="Renderable" name="GreenAlienCrouch" pivotpoint="center" texleft="0.734104" texright="0.764450" texbottom="0.00289" textop="0.033237" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
		<renderable type="Renderable" name="GreenAlienHurt" pivotpoint="center" texleft="0.767341" texright="0.797687" texbottom="0.00289" textop="0.033237" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
		<renderable type="Renderable" name="GreenAlienClimb1" pivotpoint="center" texleft="0.800578" texright="0.830924" texbottom="0.00289" textop="0.033237" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
		<renderable type="Renderable" name="GreenAlienClimb2" pivotpoint="center" texleft="0.833815" texright="0.864161" texbottom="0.00289" textop="0.033237" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
		<renderable type="Renderable" name="GreenAlienSwim1" pivotpoint="center" texleft="0.867052" texright="0.897398" texbottom="0.00289" textop="0.033237" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
		<renderable type="Renderable" name="GreenAlienSwim2" pivotpoint="center" texleft="0.900289" texright="0.930635" texbottom="0.00289" textop="0.033237" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
		<renderable type="Renderable" name="GreenAlienWalk1" pivotpoint="center" texleft="0.933526" texright="0.963872" texbottom="0.00289" textop="0.033237" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
		<renderable type="Renderable" name="GreenAlienWalk2" pivotpoint="center" texleft="0.966763" texright="0.997109" texbottom="0.00289" textop="0.033237" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
	</resources>
	<gameobject type="Player" name="Player" gravityscale="2.0" walkacceleration=".15" maxwalkspeed="5." runacceleration=".25" maxrunspeed="6." jumppower="12.0" >
		<transform x="7" y="7" z=".5" rotation="0" sx="1" sy="1" sz="1" />
		<components>
			<rigidbody type="Rigidbody" bodytype="dynamic" canrotate="false" >
				<boxcollider type="Box" name="PlayerTopCollider" width=".8" height=".85" xrel="0.0" yrel=".25" angle="0.0" density="1.0" friction=".3" issensor="false" />
				<boxcollider type="Box" name="HeadSensor" width=".25" height=".85" xrel="0.0" yrel=".3" angle="0.0" density="1.0" friction=".3" issensor="true" />
				<boxcollider type="Box" name="GroundSensor" width=".5" height=".5" xrel="0.0" yrel="-.675" angle="0.0" density="1.0" friction=".3" issensor="true" />
				<circlecollider type="Circle" name="PlayerBottomCollider" radius=".45" xrel="0.0" yrel="-.175" density="1.0" friction=".3" issensor="false" />
			</rigidbody>
			<animator type="Animator" startinganimation="0">
				<animation name="Face" frameinterval=".03" islooping="false">
					<sprite type="Sprite" name="GreenAlienFace" renderablename="GreenAlienFace" renderorder="4" isrendered="false" width="1" height="1.35" xrel="0" yrel="0" />
				</animation>
				<animation name="Jump" frameinterval=".05" islooping="false">
					<sprite type="Sprite" name="GreenAlienJump1" renderablename="GreenAlienJump1" renderorder="4" isrendered="false" width="1" height="1.35" xrel="0" yrel="0" />
					<sprite type="Sprite" name="GreenAlienJump2" renderablename="GreenAlienJump2" renderorder="4" isrendered="false" width="1" height="1.35" xrel="0" yrel="0" />
				</animation>
				<animation name="Crouch" frameinterval=".03" islooping="false">
					<sprite type="Sprite" name="GreenAlienCrouch" renderablename="GreenAlienCrouch" renderorder="4" isrendered="false" width="1" height="1.35" xrel="0" yrel="0" />
				</animation>
				<animation name="Hurt" frameinterval=".03" islooping="false">
					<sprite type="Sprite" name="GreenAlienHurt" renderablename="GreenAlienHurt" renderorder="4" isrendered="false" width="1" height="1.35" xrel="0" yrel="0" />
				</animation>
				<animation name="Climb" frameinterval=".1" islooping="true">
					<sprite type="Sprite" name="GreenAlienClimb1" renderablename="GreenAlienClimb1" renderorder="4" isrendered="false" width="1" height="1.35" xrel="0" yrel="0" />
					<sprite type="Sprite" name="GreenAlienClimb2" renderablename="GreenAlienClimb2" renderorder="4" isrendered="false" width="1" height="1.35" xrel="0" yrel="0" />
				</animation>
				<animation name="Swim" frameinterval=".1" islooping="true">
					<sprite type="Sprite" name="GreenAlienSwim1" renderablename="GreenAlienSwim1" renderorder="4" isrendered="false" width="1" height="1.35" xrel="0" yrel="0" />
					<sprite type="Sprite" name="GreenAlienSwim2" renderablename="GreenAlienSwim2" renderorder="4" isrendered="false" width="1" height="1.35" xrel="0" yrel="0" />
				</animation>
				<animation name="Walk" frameinterval=".125" islooping="true">
					<sprite type="Sprite" name="GreenAlienWalk1" renderablename="GreenAlienWalk1" renderorder="4" isrendered="false" width="1" height="1.35" xrel="0" yrel="0" />
					<sprite type="Sprite" name="GreenAlienWalk2" renderablename="GreenAlienWalk2" renderorder="4" isrendered="false" width="1" height="1.35" xrel="0" yrel="0" />
				</animation>
			</animator>
		</components>
	</gameobject>
</gob>