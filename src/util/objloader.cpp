#include "util/objloader.h"

bool loadOBJ (
  const char* path,
  std::vector <Vertex3f> * out_vertices,
  std::vector <Face3f> * out_faces
) {

  FILE * file  = fopen(path, "r");
  if (file == NULL) {
    std::cout << "Impossible to open the file!\n";
    return false;
  }

  std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
  std::vector<Vertex3f> temp_vertices;

  while(1) {
    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF) { // EOF = End of File
      break;
    }

    else { // Parse lineHeader
        if(strcmp(lineHeader, "v") == 0) {
          Vertex3f vertex;
          float x, y, z;
          fscanf(file, "%f %f %f\n", &x, &y, &z);
          vertex.moveTo(x, y, z);
          out_vertices->push_back(vertex);
        }
        else if(strcmp(lineHeader, "f") == 0) {
          std::string vertex1, vertex2, vertex3;
          unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
          int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
          if (matches != 9) {
            std::cout << "File can't be read by our simple parser\n";
            fclose(file);
            return false;
          }
          vertexIndices.push_back(vertexIndex[0]);
          vertexIndices.push_back(vertexIndex[1]);
          vertexIndices.push_back(vertexIndex[2]);
          Face3f face(vertexIndex[0], vertexIndex[1], vertexIndex[2]);
          out_faces->push_back(face);
        }
        else{
          // Probably a comment, eat up the rest of the line
          char stupidBuffer[1000];
          fgets(stupidBuffer, 1000, file);
        }

    }
  }

  fclose(file);
  return true;

}
