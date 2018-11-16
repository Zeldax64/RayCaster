#include "util/objloader.h"

bool loadOBJ (
  const char* path,
  std::vector <Vertex3f> * out_vertices,
  std::vector <Face3f> * out_faces,
  std::vector <float> * out_u,
  std::vector <float> * out_v,
  Material &out_mat,
  Color* & out_tex
) {

  FILE * file  = fopen(path, "r");
  if (file == NULL) {
    std::cout << "Impossible to open the file!\n";
    return false;
  }
  std::cout << "File opened!\n";

  std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
  std::vector<Vertex3f> temp_vertices;
  std::vector<float> temp_u;
  std::vector<float> temp_v;

  char mat_path[100];

  while(1) {
    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF) { // EOF = End of File
      break;
    }
    else { // Parse lineHeader
        if(strcmp(lineHeader, "mtllib") == 0) {
          int matches = fscanf(file, "%s\n", mat_path);
          if (matches != 1) {
            std::cout << "File can't be read by our simple parser\n";
            fclose(file);
            return false;
          }

          std::cout << mat_path << std::endl;
          loadMTL(mat_path, out_mat, out_tex);
          std::cout << "Material: " << std::endl;
          out_mat.print();
        }
        else if(strcmp(lineHeader, "v") == 0) {
          Vertex3f vertex;
          float x, y, z;
          int matches = fscanf(file, "%f %f %f\n", &x, &y, &z);
          if (matches != 3) {
            std::cout << "File can't be read by our simple parser\n";
            fclose(file);
            return false;
          }

          vertex.moveTo(x, y, z);
          out_vertices->push_back(vertex);
        }
        else if(strcmp(lineHeader, "vt") == 0) {
          float u, v;
          int matches = fscanf(file, "%f %f", &u, &v);
          if(matches != 2) {
            std::cout << "File can't be read by our simple parser\n";
            fclose(file);
            return false;
          }
          temp_u.push_back(u);
          temp_v.push_back(v);

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
          //int matches = fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);

          vertexIndices.push_back(vertexIndex[0]);
          vertexIndices.push_back(vertexIndex[1]);
          vertexIndices.push_back(vertexIndex[2]);
          
          uvIndices.push_back(uvIndex[0]);
          uvIndices.push_back(uvIndex[1]);
          uvIndices.push_back(uvIndex[2]);

          Face3f face(vertexIndex[0]-1, vertexIndex[1]-1, vertexIndex[2]-1);
          out_faces->push_back(face);


        }
        else{
          // Probably a comment, eat up the rest of the line
          char stupidBuffer[1000];
          fgets(stupidBuffer, 1000, file);
        }

    }
  }

  for (uint32_t i=0; i < vertexIndices.size(); i++) {
    
    out_u->push_back(temp_u[uvIndices[i]-1]);
    out_v->push_back(temp_v[uvIndices[i]-1]);

  }

  fclose(file);
  std::cout << "Finished!\n";
  return true;

}

// This function loads just ONE material from a .mtl file
bool loadMTL (
  const char* path,
  Material &mat,
  Color * & texture
) {

  FILE * file  = fopen(path, "r");
  if (file == NULL) {
    std::cout << "-Impossible to open .mtl file!\n";
    return false;
  }
  std::cout << "-MTL File opened!\n";

  float Ka_r, Ka_g, Ka_b;
  float Kd_r, Kd_g, Kd_b;
  float Ks_r, Ks_g, Ks_b, Ks_n;

  while(1) {
    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF) { // EOF = End of File
      break;
    }

    else { // Parse lineHeader
        if(strcmp(lineHeader, "Ka") == 0) {
          int matches = fscanf(file, "%f %f %f\n", &Ka_r, &Ka_g, &Ka_b);
          if (matches != 3) {
            std::cout << "MTL file can't be read by our simple parser\n";
            fclose(file);
            return false;
          }
        }
        else if(strcmp(lineHeader, "Kd") == 0) {
          int matches = fscanf(file, "%f %f %f\n", &Kd_r, &Kd_g, &Kd_b);
          if (matches != 3) {
            std::cout << "MTL file can't be read by our simple parser\n";
            fclose(file);
            return false;
          }
        }
        else if(strcmp(lineHeader, "Ks") == 0) {
          int matches = fscanf(file, "%f %f %f\n", &Ks_r, &Ks_g, &Ks_b);
          if (matches != 3) {
            std::cout << "MTL file can't be read by our simple parser\n";
            fclose(file);
            return false;
          }
        }
        else if(strcmp(lineHeader, "Ns") == 0) {
          int matches = fscanf(file, "%f\n", &Ks_n);
          if (matches != 1) {
            std::cout << "MTL file can't be read by our simple parser\n";
            fclose(file);
            return false;
          }
        }
        else if(strcmp(lineHeader, "map_Kd") == 0) {
          char img_path[100];
          int matches = fscanf(file, "%s\n", img_path);
          if (matches != 1) {
            std::cout << "MTLasdasdsa file can't be read by our simple parser\n";
            fclose(file);
            return false;
          }
          if(!loadImage(img_path, texture)) {
            std::cout << "Texture image could not be loaded\n";
          }

        }
        else{
          // Probably a comment, eat up the rest of the line
          char stupidBuffer[1000];
          fgets(stupidBuffer, 1000, file);
        }

    }
  }

  fclose(file);
  std::cout << "-Finished!\n";
  mat.setAmb(Ka_r, Ka_g, Ka_b);
  mat.setDif(Kd_r, Kd_g, Kd_b);
  mat.setSpe(Ks_r, Ks_g, Ks_b, Ks_n);
  return true;

}
