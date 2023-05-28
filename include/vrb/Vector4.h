/* -*- Mode: C++; tab-width: 20; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef VRB_VECTOR4_DOT_H
#define VRB_VECTOR4_DOT_H

#include "vrb/Logger.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <string>

namespace vrb {

class Vector4 {
public:
  static const Vector4& Zero();
  static const Vector4& Min();
  static const Vector4& Max();
  Vector4() {}
  Vector4(const float aX, const float aY, const float aZ, const float aW) : m(aX, aY, aZ, aW) {}
  Vector4(const Vector4& aValue) : m(aValue.m) {}
  float& x() { return m.mX; }
  float& y() { return m.mY; }
  float& z() { return m.mZ; }
  float& w() { return m.mW; }
  float x() const { return m.mX; }
  float y() const { return m.mY; }
  float z() const { return m.mZ; }
  float w() const { return m.mW; }
  Vector4& Set(const float aX, const float aY, const float aZ, const float aW) {
    m.mX = aX;
    m.mY = aY;
    m.mZ = aZ;
    m.mW = aW;
    return *this;
  }

  Vector4 operator-() const {
    Vector4 result(-m.mX, -m.mY, -m.mZ, -m.mW);
    return result;
  }

  Vector4& operator=(const Vector4& aValue) {
    m = aValue.m;
    return *this;
  }

  Vector4& operator+=(const Vector4& aValue) {
    m.mX += aValue.m.mX;
    m.mY += aValue.m.mY;
    m.mZ += aValue.m.mZ;
    m.mW += aValue.m.mW;
    return *this;
  }

  Vector4& operator-=(const Vector4& aValue) {
    m.mX -= aValue.m.mX;
    m.mY -= aValue.m.mY;
    m.mZ -= aValue.m.mZ;
    m.mW -= aValue.m.mW;
    return *this;
  }

  Vector4& operator*=(const float aValue) {
    m.mX *= aValue;
    m.mY *= aValue;
    m.mZ *= aValue;
    m.mW *= aValue;
    return *this;
  }

  Vector4& operator/=(const float aValue) {
    if (aValue != 0.0f) {
      m.mX /= aValue;
      m.mY /= aValue;
      m.mZ /= aValue;
      m.mW /= aValue;
    }
    return *this;
  }

  Vector4 operator+(const Vector4& aValue) const {
    return Vector4(
        m.mX + aValue.m.mX,
        m.mY + aValue.m.mY,
        m.mZ + aValue.m.mZ,
        m.mW + aValue.m.mW);
  }

  Vector4 operator-(const Vector4& aValue) const {
    return Vector4(
        m.mX - aValue.m.mX,
        m.mY - aValue.m.mY,
        m.mZ - aValue.m.mZ,
        m.mW - aValue.m.mW);
  }

  Vector4 operator*(const float aValue) const {
    return Vector4(*this) *= aValue;
  }

  Vector4 operator/(const float aValue) const {
    return Vector4(*this) /= aValue;
  }

  bool operator==(const Vector4& aVector4) const {
    return m.mX == aVector4.m.mX && m.mY == aVector4.m.mY && m.mZ == aVector4.m.mZ && m.mW == aVector4.m.mW;
  }

  float Magnitude() const {
    return std::sqrt(
        (m.mX * m.mX) +
        (m.mY * m.mY) +
        (m.mZ * m.mZ) +
        (m.mW * m.mW));
  }

  Vector4 Normalize() const {
    Vector4 result(*this);
    const float magnitude = Magnitude();
    if (magnitude > 0.0f) { result *= 1.0f / magnitude; }
    return result;
  }

  float Dot(const Vector4 &aValue) const {
    return (m.mX * aValue.m.mX) + (m.mY * aValue.m.mY) + (m.mZ * aValue.m.mZ) + (m.mW * aValue.m.mW);
  }


  Vector4 Cross(const Vector4 &aValue) const {
    return Vector4(
        (m.mY * aValue.m.mZ) - (m.mZ * aValue.m.mY),
        (m.mZ * aValue.m.mX) - (m.mX * aValue.m.mZ),
        (m.mX * aValue.m.mY) - (m.mY * aValue.m.mX),
        (m.mW * aValue.m.mW));
  }

  Vector4& ContractInPlace(const Vector4& aPoint) {
    m.mX = std::min(m.mX, aPoint.x());
    m.mY = std::min(m.mY, aPoint.y());
    m.mZ = std::min(m.mZ, aPoint.z());
    m.mW = std::min(m.mW, aPoint.w());
    return *this;
  }

  Vector4& ExpandInPlace(const Vector4& aPoint) {
    m.mX = std::max(m.mX, aPoint.x());
    m.mY = std::max(m.mY, aPoint.y());
    m.mZ = std::max(m.mZ, aPoint.z());
    m.mW = std::max(m.mW, aPoint.w());
    return *this;
  }

  Vector4 Contract(const Vector4& aPoint) {
    Vector4 result(*this);
    return result.ContractInPlace(aPoint);
  }

  Vector4 Expand(const Vector4& aPoint) {
    Vector4 result(*this);
    return result.ExpandInPlace(aPoint);
  }

  float* Data() { return &m.mV[0]; }
  const float* Data() const { return &m.mV[0]; }

  std::string ToString() const {
    std::string result("(");
    result += std::to_string(m.mX) + ", "
        + std::to_string(m.mY) + ", "
        + std::to_string(m.mZ) + ", "
        + std::to_string(m.mW) + ")";
    return result;
  }

protected:
  union Data {
    float mV[4];
    struct {
      float mX, mY, mZ, mW;
    };
    Data() : mX(0.0f), mY(0.0f), mZ(0.0f), mW(0.0f) {}
    Data(const float aX, const float aY, const float aZ, const float aW) : mX(aX), mY(aY), mZ(aZ), mW(aW) {}
    Data(const Data& aData) : mX(aData.mX), mY(aData.mY), mZ(aData.mZ), mW(aData.mW) {}
    Data& operator=(const Data& aData) {
      mX = aData.mX;
      mY = aData.mY;
      mZ = aData.mZ;
      mW = aData.mW;
      return *this;
    }
  };

  union Data m;
};

}

#endif // VRB_VECTOR4_DOT_H
