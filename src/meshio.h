/*
    meshio.h: Mesh file input/output routines

    This file is part of the implementation of

        Instant Field-Aligned Meshes
        Wenzel Jakob, Daniele Panozzo, Marco Tarini, and Olga Sorkine-Hornung
        In ACM Transactions on Graphics (Proc. SIGGRAPH Asia 2015)

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#pragma once

#include "common.h"
#include <exception>
#include <map>

extern void
load_mesh_or_pointcloud(const std::string &filename, MatrixXu &F, MatrixXf &V,
                        MatrixXf &N, int meshIndex = -1,
                        bool validateMultiMesh = true,
                        const ProgressCallback &progress = ProgressCallback());

extern void load_obj(const std::string &filename, MatrixXu &F, MatrixXf &V,
                     const ProgressCallback &progress = ProgressCallback());

extern void load_ply(const std::string &filename, MatrixXu &F, MatrixXf &V,
                     MatrixXf &N, bool pointcloud = false,
                     const ProgressCallback &progress = ProgressCallback());

extern void
load_pointcloud(const std::string &filename, MatrixXf &V, MatrixXf &N,
                const ProgressCallback &progress = ProgressCallback());

struct MultiMeshException : public std::exception {
  std::string filename;
  std::map<int, std::string> meshes;
  MultiMeshException(const std::string &f, const std::map<int, std::string> &m)
      : filename(f), meshes(m) {}
  const char *what() const noexcept override {
    return "Multiple meshes detected";
  }
};

extern void
load_assimp_common(const std::string &filename, MatrixXu &F, MatrixXf &V,
                   MatrixXf &N, int meshIndex = -1,
                   bool validateMultiMesh = false,
                   const ProgressCallback &progress = ProgressCallback());

extern void write_mesh(const std::string &filename, const MatrixXu &F,
                       const MatrixXf &V, const MatrixXf &N = MatrixXf(),
                       const MatrixXf &Nf = MatrixXf(),
                       const MatrixXf &UV = MatrixXf(),
                       const MatrixXf &C = MatrixXf(),
                       const ProgressCallback &progress = ProgressCallback());

extern void write_obj(const std::string &filename, const MatrixXu &F,
                      const MatrixXf &V, const MatrixXf &N = MatrixXf(),
                      const MatrixXf &Nf = MatrixXf(),
                      const MatrixXf &UV = MatrixXf(),
                      const MatrixXf &C = MatrixXf(),
                      const ProgressCallback &progress = ProgressCallback());

extern void write_ply(const std::string &filename, const MatrixXu &F,
                      const MatrixXf &V, const MatrixXf &N = MatrixXf(),
                      const MatrixXf &Nf = MatrixXf(),
                      const MatrixXf &UV = MatrixXf(),
                      const MatrixXf &C = MatrixXf(),
                      const ProgressCallback &progress = ProgressCallback());
