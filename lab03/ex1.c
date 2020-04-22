void write_sighting(FILE *f, struct pod *p);
void write_sightings_file(char filename[],  struct pod *first_pod) {
	FILE *file = fopen(filename."r");

	struct pod *current = first_pod;
	while (current != NULL) {
		write(current->data);
		current = current->next;
	}
	close(filename);
