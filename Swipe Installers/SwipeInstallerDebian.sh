echo 'Installing g++'
sudo apt-get install g++ -y

echo 'Installing sdl'
sudo apt-get install libsdl2-dev -y
echo 'Installing sdl image'
sudo apt-get install libsdl2-image-dev -y
echo 'Installing sdl ttf'
sudo apt-get install libsdl2-ttf-dev -y
echo 'Installing sdl mixer'
sudo apt-get install libsdl2-mixer-dev -y

if dpkg -s git &>/dev/null; then
        GIT='installed'
        echo 'git already installed'
else
        GIT='not installed'
        echo 'Installing git'
        sudo apt-get install git -y
fi

echo 'Cloning repo'

if git clone https://github.com/Upsidedrop/Swipe-Visual-Coding.git; then
	if mkdir Swipe; then
		mkdir Swipe/bin
		mkdir Swipe/bin/release
		
		echo 'Compiling program'
		
		cd Swipe-Visual-Coding
		g++ -c src/*.cpp -std=c++14 -m64 -O2 -Wall -I include
	       	cd ..
		g++ Swipe-Visual-Coding/*.o -o Swipe/bin/release/main -s -lSDL2main -lSDL2_ttf -lSDL2 -lSDL2_image -lSDL2_mixer
		
		echo 'Copying resources'
		cp -r Swipe-Visual-Coding/res Swipe/bin/release/res
	else
		echo 'Halt'
	fi
	rm -rf Swipe-Visual-Coding
else
	echo 'Halt'
fi

if [[ $GIT == 'not installed' ]]; then
        echo 'Removing git'
	sudo apt-get autoremove git -y
	sudo apt-get purge git -y
fi
