<?xml version="1.0" encoding="UTF-8" ?>
<go>
    <resources>
        <renderable type="Renderable" name="CoinGold" pivotpoint="center" texleft="0.601156" texright="0.631503" texbottom="0.0693642" textop="0.099711" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="GreenAlienCoin" pivotpoint="center" texleft="0.634393" texright="0.66474" texbottom="0.169075" textop="0.199422" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="HUD0" pivotpoint="center" texleft="0.468208" texright="0.498555" texbottom="0.468208" textop="0.498555" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="HUD1" pivotpoint="center" texleft="0.501445" texright="0.531792" texbottom="0.468208" textop="0.498555" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="HUD2" pivotpoint="center" texleft="0.534682" texright="0.565029" texbottom="0.468208" textop="0.498555" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="HUD3" pivotpoint="center" texleft="0.567919" texright="0.598266" texbottom="0.468208" textop="0.498555" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="HUD4" pivotpoint="center" texleft="0.601156" texright="0.631503" texbottom="0.468208" textop="0.498555" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="HUD5" pivotpoint="center" texleft="0.634393" texright="0.66474" texbottom="0.468208" textop="0.498555" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="HUD6" pivotpoint="center" texleft="0.434971" texright="0.465318" texbottom="0.501445" textop="0.531792" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="HUD7" pivotpoint="center" texleft="0.468208" texright="0.498555" texbottom="0.501445" textop="0.531792" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="HUD8" pivotpoint="center" texleft="0.501445" texright="0.531792" texbottom="0.501445" textop="0.531792" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="HUD9" pivotpoint="center" texleft="0.534682" texright="0.565029" texbottom="0.501445" textop="0.531792" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="HUDx" pivotpoint="center" texleft="0.567919" texright="0.598266" texbottom="0.501445" textop="0.531792" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="KeyYellow" pivotpoint="center" texleft="0.434971" texright="0.465318" texbottom="0.434971" textop="0.465318" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="KeyGreen" pivotpoint="center" texleft="0.468208" texright="0.498555" texbottom="0.434971" textop="0.465318" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="KeyRed" pivotpoint="center" texleft="0.501445" texright="0.531792" texbottom="0.434971" textop="0.465318" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="KeyBlue" pivotpoint="center" texleft="0.534682" texright="0.565029" texbottom="0.434971" textop="0.465318" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="KeyYellowEmpty" pivotpoint="center" texleft="0.567919" texright="0.598266" texbottom="0.434971" textop="0.465318" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="KeyGreenEmpty" pivotpoint="center" texleft="0.601156" texright="0.631503" texbottom="0.434971" textop="0.465318" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="KeyRedEmpty" pivotpoint="center" texleft="0.634393" texright="0.66474" texbottom="0.434971" textop="0.465318" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
        <renderable type="Renderable" name="KeyBlueEmpty" pivotpoint="center" texleft="0.434971" texright="0.465318" texbottom="0.468208" textop="0.498555" texturefile="data/spritesheets/spritesheet.png" shaderfile="data/shaders/BasicTextureShader" />
    </resources>
	<gameobject type="HUD" name="PlayerHud">
		<transform x="0" y="0" z="0" rotation="0" sx="1" sy="1" sz="1" />
		<components>
			<sprite type="Sprite" name="KeyYellowOutline" renderablename="KeyYellowEmpty" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.05" yrel="0.95" />
			<sprite type="Sprite" name="KeyGreenOutline" renderablename="KeyGreenEmpty" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.1" yrel="0.95" />
			<sprite type="Sprite" name="KeyRedOutline" renderablename="KeyRedEmpty" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.15" yrel="0.95" />
			<sprite type="Sprite" name="KeyBlueOutline" renderablename="KeyBlueEmpty" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.2" yrel="0.95" />
			<sprite type="Sprite" name="KeyYellow" renderablename="KeyYellow" renderorder="5" isrendered="true" width="0.9" height="0.9" xrel="0.05" yrel="0.95" />
			<sprite type="Sprite" name="KeyGreen" renderablename="KeyGreen" renderorder="5" isrendered="true" width="0.9" height="0.9" xrel="0.1" yrel="0.95" />
			<sprite type="Sprite" name="KeyRed" renderablename="KeyRed" renderorder="5" isrendered="true" width="0.9" height="0.9" xrel="0.15" yrel="0.95" />
			<sprite type="Sprite" name="KeyBlue" renderablename="KeyBlue" renderorder="5" isrendered="true" width="0.9" height="0.9" xrel="0.2" yrel="0.95" />
			<sprite type="Sprite" name="Coins" renderablename="CoinGold" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.3" yrel="0.95" />
			<sprite type="Sprite" name="X" renderablename="HUDx" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.325" yrel="0.95" />
			<sprite type="Sprite" name="CoinTens" renderablename="HUD0" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.35" yrel="0.95" />
			<sprite type="Sprite" name="CoinOnes" renderablename="HUD0" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.375" yrel="0.95" />
			<sprite type="Sprite" name="TimerHundreds" renderablename="HUD0" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.425" yrel="0.95" />
			<sprite type="Sprite" name="TimerTens" renderablename="HUD0" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.45" yrel="0.95" />
			<sprite type="Sprite" name="TimerOnes" renderablename="HUD0" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.475" yrel="0.95" />
			<sprite type="Sprite" name="PlayerCoin" renderablename="GreenAlienCoin" renderorder="6" isrendered="true" width="1.0" height="1.0" xrel="0.75" yrel="0.95" />
			<sprite type="Sprite" name="X" renderablename="HUDx" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.775" yrel="0.95" />
			<sprite type="Sprite" name="ScoreMillions" renderablename="HUD0" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.8" yrel="0.95" />
			<sprite type="Sprite" name="ScoreHundredThousands" renderablename="HUD0" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.825" yrel="0.95" />
			<sprite type="Sprite" name="ScoreTenThousands" renderablename="HUD0" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.85" yrel="0.95" />
			<sprite type="Sprite" name="ScoreThousands" renderablename="HUD0" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.875" yrel="0.95" />
			<sprite type="Sprite" name="ScoreHundreds" renderablename="HUD0" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.9" yrel="0.95" />
			<sprite type="Sprite" name="ScoreTens" renderablename="HUD0" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.925" yrel="0.95" />
			<sprite type="Sprite" name="ScoreOnes" renderablename="HUD0" renderorder="5" isrendered="true" width="1.0" height="1.0" xrel="0.95" yrel="0.95" />
		</components>
	</gameobject>
</go>
