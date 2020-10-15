#!/bin/sh

../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Fant_Jaune Fant_Jaune.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Fant_Rouge Fant_Rouge.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Fant_Bleu Fant_Bleu.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Fant_Rose Fant_Rose.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Fant_Vuln Fant_Vuln.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Melon Melon.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Cerise Cerise.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Fraise Fraise.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Orange Orange.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Truc Truc.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Pomme Pomme.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Pacman_Bas Pacman_Bas.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Pacman_Bas_2 Pacman_Bas_2.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Pacman_Droit Pacman_Droit.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Pacman_Droit_2 Pacman_Droit_2.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Pacman_Gauche Pacman_Gauche.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Pacman_Gauche_2 Pacman_Gauche_2.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Pacman_Haut Pacman_Haut.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Pacman_Haut_2 Pacman_Haut_2.bmp
../../../../../PackBitmap/PackBitmap/bin/Debug/PackBitmap.exe -l=ada -c=8 Pac_Gum Pac_Gum.bmp

arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c melon_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c cerise_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c fant_bleu_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c fant_rouge_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c fant_rose_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c fant_jaune_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c fant_vuln_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c fraise_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c orange_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c pacman_bas_2_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c pacman_bas_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c pacman_droit_2_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c pacman_droit_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c pacman_gauche_2_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c pacman_gauche_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c pacman_haut_2_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c pacman_haut_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c pomme_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c truc_res.ads
arm-none-eabi-gcc -gdwarf-2 -O3 --function-sections -march=armv7e-m -mthumb -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I. -I/usr/local/arm-ada/lib-appli/ -c pac_gum_res.ads

cp -v *.ads *.ali *.o ../../
