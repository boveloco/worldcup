﻿/******************************************************************************
 *
 * COPYRIGHT Vinicius G. Mendonca ALL RIGHTS RESERVED.
 * Acknowledgments to Ráfagan Abreu for review and support since 2011 (kids grow fast).
 *
 * This software cannot be copied, stored, distributed without
 * Vinicius G.Mendonca prior authorization.
 *
 * This file was made available on http://www.pontov.com.br and it is free
 * to be restributed or used under Creative Commons license 2.5 br:
 * http://creativecommons.org/licenses/by-sa/2.5/br/
 *
 *******************************************************************************
 * Este software nao pode ser copiado, armazenado, distribuido sem autorizacao
 * a priori de Vinicius G. Mendonca
 *
 * Este arquivo foi disponibilizado no site http://www.pontov.com.br e esta
 * livre para distribuição seguindo a licença Creative Commons 2.5 br:
 * http://creativecommons.org/licenses/by-sa/2.5/br/
 *
 ******************************************************************************/


#ifndef __OF_DRAW_H__
#define __OF_DRAW_H__

#include "ofMain.h"
#include "Matrix3.h"
#include "Vector2D.h"
#include "AffineTransform.h"
#include "BoundingCircle.h"

 //OpenFrameworks trabalha com regra da mão esquerda
inline void __draw(const ofMatrix4x4 matrix, const ofImage& img) {
	ofPushMatrix();
	ofMultMatrix(matrix);
	img.draw(-img.getWidth() / 2.0f, -img.getHeight() / 2.0f);
	ofPopMatrix();
}

inline void __drawSubsection(const ofMatrix4x4 matrix, const math::Vector2D& dimensions, const ofImage& img, unsigned int index) {
	unsigned int numQuads[2] = {
		static_cast<unsigned int>(img.getWidth() / dimensions.x),
		static_cast<unsigned int>(img.getHeight() / dimensions.y)
	};
	auto maxIndex = numQuads[0] * numQuads[1];
	index = index % maxIndex;
	auto quadLeftUpCorner = math::Vector2D(dimensions.x * (index % numQuads[0]), dimensions.y * floor(index / numQuads[0]));

	ofPushMatrix();
	ofMultMatrix(matrix);
	img.drawSubsection(
		-dimensions.x / 2.0f, -dimensions.y / 2.0f,
		dimensions.x, dimensions.y, quadLeftUpCorner.x, quadLeftUpCorner.y);
	ofPopMatrix();
}

namespace math {
	namespace lh {
		inline Matrix3 flipY(const Matrix3& matrix) {
			auto m = matrix;
			m.set(2, 1, -m.get(2, 1));
			m *= newAffineTranslation(0, ofGetHeight());
			return m;
		}

	    inline ofMatrix4x4 newMatrix4x4(const Matrix3& m) {
            ofMatrix4x4 m4x4(
                             m.a(), m.b(), m.c(), 0.0f,
                             m.d(), m.e(), m.f(), 0.0f,
                             0.0,  0.0f, 1.0f,  0.0f,
                             m.g(), m.h(), m.k(), 1.0f);
            return m4x4;
        }

	    inline void draw(const Matrix3& matrix, const ofImage& img) {
            __draw(newMatrix4x4(matrix), img);
        }

		inline void draw(const Matrix3& matrix, const ofImage& img, const Vector2D& dimensions, unsigned int index) {
			__drawSubsection(newMatrix4x4(matrix), dimensions, img, index);
		}
    }
}

namespace math {
    namespace rh {
		//Fato curioso: Apesar das translações funcionarem com o y invertido, as rotações são corrigidas pela OpenFrameworks, o que é bizarro
		// Sendo assim, só precisamos inverter a translação em y
		// Se a OF não corrigisse a rotação, poderíamos multiplicar a matriz por uma reflexão: newAffineScale(1, -1)
		inline Matrix3 flipY(const Matrix3& matrix) {
			auto m = matrix;
			m.set(1, 2, -m.get(1, 2));
			m = newAffineTranslation(0, ofGetHeight()) * m;
			return m;
		}

	    inline ofMatrix4x4 newMatrix4x4(const Matrix3& m) {
            ofMatrix4x4 m4x4(
                             m.a(), m.d(), m.g(), 0.0f,
                             m.b(), m.e(), m.h(), 0.0f,
                             0.0,  0.0f, 1.0f,  0.0f,
                             m.c(), m.f(), m.k(), 1.0f);
            return m4x4;
        }

	    inline void draw(const Matrix3& matrix, const ofImage& img) {
            __draw(newMatrix4x4(matrix), img);
        }

		inline void draw(const Matrix3& matrix, const ofImage& img, const Vector2D& dimensions, unsigned int index) {
			__drawSubsection(newMatrix4x4(matrix), dimensions, img, index);
		}
    }
}

//class ofAABB_DrawHelper : public math::IAABB_DrawHelper
//{
//public:
//	void draw(const math::AABB& box, bool invertY = true) const override {
//		ofNoFill();
//		ofDrawRectangle(
//			box.position.x, 
//			invertY ? (ofGetHeight() - box.position.y - box.size.y) : box.position.y, 
//			box.size.x, box.size.y);
//		ofFill();
//	};
//	
//	~ofAABB_DrawHelper() override {};
//};
//
//class ofBC_DrawHelper : public math::IBoundingCircleDrawHelper
//{
//public:
//	void draw(const math::BoundingCircle& circle, bool invertY = true) const override {
//		ofNoFill();
//		ofDrawCircle(
//			circle.position.x,
//			invertY ? (ofGetHeight() - circle.position.y) : circle.position.y,
//			circle.radius);
//		ofFill();
//	};
//
//	~ofBC_DrawHelper() override {};
//};

#endif //__OF_DRAW_H__