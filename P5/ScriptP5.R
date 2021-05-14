#Loading libraries
library(tuneR)
library(seewave)
library(audio)

#Loading audio files
perro <- readWave('C:/Users/pacoa/Desktop/PDIH/P5/perro.wav')
perro
gato <- readMP3('C:/Users/pacoa/Desktop/PDIH/P5/gato.mp3')
gato

#Plotting waves
plot( extractWave(perro, from = 1, to = 159732) )
plot( extractWave(gato, from = 1, to = 393984) )

#Characteristics
str(perro)
str(gato)

#Union
s1 <- pastew(perro, gato, output="Wave")
plot( extractWave(s1, from = 1, to = 553716 ))
listen(s1)

f <- 44100

#Delete frequencies
sndF1 <- bwfilter(s1, f=f, channel=1, n=1, from=10000, to=20000, bandpass=TRUE, listen = FALSE, output = "Wave")
listen(sndF1,f=f)

#Save
writeWave(sndF1, file.path('C:/Users/pacoa/Desktop/PDIH/P5/mezcla.wav') )

#Loading file
mezcla <-  readWave('C:/Users/pacoa/Desktop/PDIH/P5/mezcla.wav')

#ECO
mezclaECO <- echo(mezcla,f=22050,amp=c(0.8,0.4,0.2),delay=c(1,2,3),
                output="Wave")
mezclaECO@left <- 10000 * mezclaECO@left

#Turn
alreves <- revw(mezclaECO, output="Wave")
listen(alreves)

#Save
writeWave(alreves, file.path("C:/Users/pacoa/Desktop/PDIH/P5/alreves.wav") )

