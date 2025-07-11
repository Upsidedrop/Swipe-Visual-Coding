echo 'Installing g++'
sudo pacman -S gcc --noconfirm

if pacman -Q sdl2 &>/dev/null; then
        echo 'sdl already installed'
else
        echo 'Installing sdl'
        sudo pacman -S sdl2-compat --noconfirm
fi

echo 'Installing sdl image'
sudo pacman -S sdl2_image --noconfirm
echo 'Installing sdl ttf'
sudo pacman -S sdl2_ttf --noconfirm
echo 'Installing sdl mixer'
sudo pacman -S sdl2_mixer --noconfirm

if pacman -Q git &>/dev/null; then
        GIT='installed'
        echo 'git already installed'
else
        GIT='not installed'
        echo 'Installing git'
        sudo pacman -S git --noconfirm
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
	sudo pacman -Rs git
fi
