# Pagination

- une table des pages par processus
- Bitmap pour la mémoire physique
- Addspace.cc Read At Physique = virtuel , prendre en compte les

machine->


executable->ReadAt (&(machine->mainMemory[noffH.code.virtualAddr]),
			      noffH.code.size, noffH.code.inFileAddr);

L'adresse virtuelle sert d'index pour l'adresse  physique. La mémoire virtuelle est un mirroir de la mémoire physique

Pourquoi faut-il unseul objet de cette classePageProvider?On pourra donc le créer en même temps que la machine dansInitialize.

Y'a qu'une seule zone memoire donc si il y avait plus de une instance de cette classe, ils pouraient donner, des zones déja allouées et ou mal gérer la mémoire.


