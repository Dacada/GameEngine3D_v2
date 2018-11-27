#include <Base/engine3D_growingArray.h>
#include <Base/engine3D_strToIntMap.h>
#include <Base/engine3D_time.h>
#include <Base/engine3D_vector.h>
#include <Base/engine3D_util.h>
#include <check.h>

START_TEST(GrowingArrayWithFinish) {
	engine3D_growingArray_t arr;
	engine3D_growingArray_init(&arr, sizeof(double), 8);

	for (int i = 0; i < 1000; i++) {
		double *element = (double*)engine3D_growingArray_add(&arr);
		*element = (double)i;
	}

	double *elements = (double*)engine3D_growingArray_finish(&arr, true);

	for (int i = 0; i < 1000; i++) {
		ck_assert_double_eq((double)i, elements[i]);
	}

	free(elements);
}
END_TEST;

START_TEST(GrowingArrayWithoutFinish) {
	engine3D_growingArray_t arr;
	engine3D_growingArray_init(&arr, sizeof(double), 8);

	engine3D_growingArray_ensureGrowth(&arr, 1000);

	for (int i = 0; i < 1000; i++) {
		double *element = (double*)engine3D_growingArray_add(&arr);
		*element = (double)i;
	}

	double *elements = (double*)engine3D_growingArray_finish(&arr, false);

	for (int i = 0; i < 1000; i++) {
		ck_assert_double_eq((double)i, elements[i]);
	}

	free(elements);
}
END_TEST;

START_TEST(StrToIntMapNoCollision) {
	engine3D_strToIntMap_t *map = engine3D_strToIntMap_new();
	engine3D_strToIntMap_init(map);
	engine3D_strToIntMap_add(map, "a", 1);
	engine3D_strToIntMap_add(map, "b", 2);
	engine3D_strToIntMap_add(map, "c", 3);
	engine3D_strToIntMap_add(map, "d", 4);
	engine3D_strToIntMap_add(map, "e", 5);
	engine3D_strToIntMap_add(map, "f", 6);
	engine3D_strToIntMap_add(map, "g", 7);
	engine3D_strToIntMap_add(map, "h", 8);
	engine3D_strToIntMap_add(map, "i", 9);
	engine3D_strToIntMap_add(map, "j", 10);
	engine3D_strToIntMap_add(map, "k", 11);
	ck_assert_int_eq(1, engine3D_strToIntMap_get(map, "a"));
	ck_assert_int_eq(2, engine3D_strToIntMap_get(map, "b"));
	ck_assert_int_eq(3, engine3D_strToIntMap_get(map, "c"));
	ck_assert_int_eq(4, engine3D_strToIntMap_get(map, "d"));
	ck_assert_int_eq(5, engine3D_strToIntMap_get(map, "e"));
	ck_assert_int_eq(6, engine3D_strToIntMap_get(map, "f"));
	ck_assert_int_eq(7, engine3D_strToIntMap_get(map, "g"));
	ck_assert_int_eq(8, engine3D_strToIntMap_get(map, "h"));
	ck_assert_int_eq(9, engine3D_strToIntMap_get(map, "i"));
	ck_assert_int_eq(10, engine3D_strToIntMap_get(map, "j"));
	ck_assert_int_eq(11, engine3D_strToIntMap_get(map, "k"));
	engine3D_strToIntMap_destroy(map);
	free(map);
}
END_TEST;

START_TEST(StrToIntMapWithCollision) {
	engine3D_strToIntMap_t *map = engine3D_strToIntMap_new();
	engine3D_strToIntMap_init(map);
	engine3D_strToIntMap_add(map, "aat", 1);
	engine3D_strToIntMap_add(map, "aqd", 2);
	engine3D_strToIntMap_add(map, "boe", 3);
	engine3D_strToIntMap_add(map, "cmf", 4);
	engine3D_strToIntMap_add(map, "dkg", 5);
	engine3D_strToIntMap_add(map, "dzx", 6);
	engine3D_strToIntMap_add(map, "eih", 7);
	engine3D_strToIntMap_add(map, "exy", 8);
	engine3D_strToIntMap_add(map, "fgi", 9);
	engine3D_strToIntMap_add(map, "fvz", 10);
	engine3D_strToIntMap_add(map, "gej", 11);
	ck_assert_int_eq(1, engine3D_strToIntMap_get(map, "aat"));
	ck_assert_int_eq(2, engine3D_strToIntMap_get(map, "aqd"));
	ck_assert_int_eq(3, engine3D_strToIntMap_get(map, "boe"));
	ck_assert_int_eq(4, engine3D_strToIntMap_get(map, "cmf"));
	ck_assert_int_eq(5, engine3D_strToIntMap_get(map, "dkg"));
	ck_assert_int_eq(6, engine3D_strToIntMap_get(map, "dzx"));
	ck_assert_int_eq(7, engine3D_strToIntMap_get(map, "eih"));
	ck_assert_int_eq(8, engine3D_strToIntMap_get(map, "exy"));
	ck_assert_int_eq(9, engine3D_strToIntMap_get(map, "fgi"));
	ck_assert_int_eq(10, engine3D_strToIntMap_get(map, "fvz"));
	ck_assert_int_eq(11, engine3D_strToIntMap_get(map, "gej"));
	engine3D_strToIntMap_destroy(map);
	free(map);
}
END_TEST;

START_TEST(GetTimeTest) {
	engine3D_timer_init();
	double t = engine3D_timer_getTime();
	engine3D_time_sleep(0.1);
	double diff = engine3D_timer_getTime() - t;

	ck_assert_double_eq_tol(0.1, diff, 0.01);
}
END_TEST;

START_TEST(Vector2fLengthTest) {
	engine3D_vector2f_t v;
	v.x = 3;
	v.y = 4;
	float r = engine3D_vector2f_length(v);
	ck_assert_float_eq(5.0f, r);
}
END_TEST;

START_TEST(Vector2fDotTest) {
	engine3D_vector2f_t v1, v2;
	v1.x = 1;
	v1.y = 2;
	v2.x = 4;
	v2.y = 8;
	float r = engine3D_vector2f_dot(v1, v2);
	ck_assert_float_eq(20.0f, r);
}
END_TEST;

START_TEST(Vector2fCrossTest) {
	engine3D_vector2f_t v1, v2;
	v1.x = 1;
	v1.y = 2;
	v2.x = 4;
	v2.y = 8;
	float r = engine3D_vector2f_cross(v1, v2);
	ck_assert_float_eq(0.0f, r);
}
END_TEST;

START_TEST(Vector2fNormalizeTest) {
	engine3D_vector2f_t v;
	v.x = 3;
	v.y = 4;
	engine3D_vector2f_normalize(&v);
	ck_assert_float_eq(0.6f, v.x);
	ck_assert_float_eq(0.8f, v.y);
}
END_TEST;

START_TEST(Vector2fRotateTest) {
	engine3D_vector2f_t v, r;
	v.x = 1;
	v.y = 0;
	r = engine3D_vector2f_rotateRad(v, TO_RADIANS(45));
	ck_assert_float_eq_tol(0.707f, r.x, 0.001f);
	ck_assert_float_eq_tol(0.707f, r.y, 0.001f);
}
END_TEST;

START_TEST(Vector2fAddTest) {
	engine3D_vector2f_t v1, v2, r;
	v1.x = 4;
	v1.y = 5;
	v2.x = 8;
	v2.y = 2;
	r = engine3D_vector2f_add(v1, v2);
	ck_assert_float_eq(12.0f, r.x);
	ck_assert_float_eq(7.0f, r.y);
}
END_TEST;

START_TEST(Vector2fAddfTest) {
	engine3D_vector2f_t v, r;
	v.x = 4;
	v.y = 5;
	r = engine3D_vector2f_addf(v, 3);
	ck_assert_float_eq(7.0f, r.x);
	ck_assert_float_eq(8.0f, r.y);
}
END_TEST;

START_TEST(Vector2fSubTest) {
	engine3D_vector2f_t v1, v2, r;
	v1.x = 4;
	v1.y = 5;
	v2.x = 8;
	v2.y = 2;
	r = engine3D_vector2f_sub(v1, v2);
	ck_assert_float_eq(-4.0f, r.x);
	ck_assert_float_eq(3.0f, r.y);
}
END_TEST;

START_TEST(Vector2fSubfTest) {
	engine3D_vector2f_t v, r;
	v.x = 4;
	v.y = 5;
	r = engine3D_vector2f_subf(v, 3);
	ck_assert_float_eq(1.0f, r.x);
	ck_assert_float_eq(2.0f, r.y);
}
END_TEST;

START_TEST(Vector2fMulTest) {
	engine3D_vector2f_t v1, v2, r;
	v1.x = 4;
	v1.y = 5;
	v2.x = 8;
	v2.y = 2;
	r = engine3D_vector2f_mul(v1, v2);
	ck_assert_float_eq(32.0f, r.x);
	ck_assert_float_eq(10.0f, r.y);
}
END_TEST;

START_TEST(Vector2fMulfTest) {
	engine3D_vector2f_t v, r;
	v.x = 4;
	v.y = 5;
	r = engine3D_vector2f_mulf(v, 3);
	ck_assert_float_eq(12.0f, r.x);
	ck_assert_float_eq(15.0f, r.y);
}
END_TEST;

START_TEST(Vector2fDivTest) {
	engine3D_vector2f_t v1, v2, r;
	v1.x = 4;
	v1.y = 5;
	v2.x = 8;
	v2.y = 2;
	r = engine3D_vector2f_div(v1, v2);
	ck_assert_float_eq(0.5f, r.x);
	ck_assert_float_eq(2.5f, r.y);
}
END_TEST;

START_TEST(Vector2fDivfTest) {
	engine3D_vector2f_t v, r;
	v.x = 4;
	v.y = 5;
	r = engine3D_vector2f_divf(v, 3);
	ck_assert_float_eq_tol(1.3f, r.x, 0.1f);
	ck_assert_float_eq_tol(1.6f, r.y, 0.1f);
}
END_TEST;

START_TEST(Vector2fLerpTest) {
  engine3D_vector2f_t v1, v2, r;
  v1.x = 4;
  v1.y = 9;
  v2.x = 1;
  v2.y = 3;
  r = engine3D_vector2f_lerp(v1, v2, 0.5f);
  ck_assert_float_eq_tol(2.5f, r.x, 0.1f);
  ck_assert_float_eq_tol(6.0f, r.y, 0.1f);
}
END_TEST;

START_TEST(Vector2fEqualTest) {
  engine3D_vector2f_t v1, v2;
  v1.x = 4;
  v1.y = 9;
  v2.x = 1;
  v2.y = 3;
  ck_assert(!engine3D_vector2f_equal(v1, v2));
  v2.x = 4;
  v2.y = 9;
  ck_assert(engine3D_vector2f_equal(v1, v2));
}
END_TEST;

START_TEST(Vector3fDotTest) {
	engine3D_vector3f_t v1, v2;
	v1.x = 1;
	v1.y = 2;
	v1.z = -5;
	v2.x = 4;
	v2.y = 8;
	v2.z = 1;
	float r = engine3D_vector3f_dot(v1, v2);
	ck_assert_float_eq(15.0f, r);
}
END_TEST;

START_TEST(Vector3fNormalizeTest) {
	engine3D_vector3f_t v;
	v.x = 3;
	v.y = 1;
	v.z = 2;
	engine3D_vector3f_normalize(&v);
	ck_assert_float_eq_tol(0.802f, v.x, 0.001f);
	ck_assert_float_eq_tol(0.267f, v.y, 0.001f);
	ck_assert_float_eq_tol(0.534f, v.z, 0.001f);
}
END_TEST;

START_TEST(Vector3fRotateTest) {
	engine3D_vector3f_t v, a, r;
	v.x = 1;
	v.y = 0;
	v.z = 5;
	a.x = 1;
	a.y = 2;
	a.z = 3;
	r = engine3D_vector3f_rotateRad(v, TO_RADIANS(45), a);
	ck_assert_float_eq_tol(10.561f, r.x, 0.001f);
	ck_assert_float_eq_tol(7.958f, r.y, 0.001f);
	ck_assert_float_eq_tol(6.661f, r.z, 0.001f);
}
END_TEST;

START_TEST(Vector3fCrossTest) {
	engine3D_vector3f_t v1, v2, r;
	v1.x = 3;
	v1.y = -3;
	v1.z = 1;
	v2.x = 4;
	v2.y = 9;
	v2.z = 2;
	r = engine3D_vector3f_cross(v1, v2);
	ck_assert_float_eq(-15.0f, r.x);
	ck_assert_float_eq(-2.0f, r.y);
	ck_assert_float_eq(39.0f, r.z);
}
END_TEST;

START_TEST(Vector3fAddTest) {
	engine3D_vector3f_t v1, v2, r;
	v1.x = 4;
	v1.y = 5;
	v1.z = 7;
	v2.x = 8;
	v2.y = 2;
	v2.z = 1;
	r = engine3D_vector3f_add(v1, v2);
	ck_assert_float_eq(12.0f, r.x);
	ck_assert_float_eq(7.0f, r.y);
	ck_assert_float_eq(8.0f, r.z);
}
END_TEST;

START_TEST(Vector3fAddfTest) {
	engine3D_vector3f_t v, r;
	v.x = 4;
	v.y = 5;
	v.z = 7;
	r = engine3D_vector3f_addf(v, 3);
	ck_assert_float_eq(7.0f, r.x);
	ck_assert_float_eq(8.0f, r.y);
	ck_assert_float_eq(10.0f, r.z);
}
END_TEST;

START_TEST(Vector3fSubTest) {
	engine3D_vector3f_t v1, v2, r;
	v1.x = 4;
	v1.y = 5;
	v1.z = 7;
	v2.x = 8;
	v2.y = 2;
	v2.z = 1;
	r = engine3D_vector3f_sub(v1, v2);
	ck_assert_float_eq(-4.0f, r.x);
	ck_assert_float_eq(3.0f, r.y);
	ck_assert_float_eq(6.0f, r.z);
}
END_TEST;

START_TEST(Vector3fSubfTest) {
	engine3D_vector3f_t v, r;
	v.x = 4;
	v.y = 5;
	v.z = 7;
	r = engine3D_vector3f_subf(v, 3);
	ck_assert_float_eq(1.0f, r.x);
	ck_assert_float_eq(2.0f, r.y);
	ck_assert_float_eq(4.0f, r.z);
}
END_TEST;

START_TEST(Vector3fMulTest) {
	engine3D_vector3f_t v1, v2, r;
	v1.x = 4;
	v1.y = 5;
	v1.z = 7;
	v2.x = 8;
	v2.y = 2;
	v2.z = 1;
	r = engine3D_vector3f_mul(v1, v2);
	ck_assert_float_eq(32.0f, r.x);
	ck_assert_float_eq(10.0f, r.y);
	ck_assert_float_eq(7.0f, r.z);
}
END_TEST;

START_TEST(Vector3fMulfTest) {
	engine3D_vector3f_t v, r;
	v.x = 4;
	v.y = 5;
	v.z = 7;
	r = engine3D_vector3f_mulf(v, 3);
	ck_assert_float_eq(12.0f, r.x);
	ck_assert_float_eq(15.0f, r.y);
	ck_assert_float_eq(21.0f, r.z);
}
END_TEST;

START_TEST(Vector3fDivTest) {
	engine3D_vector3f_t v1, v2, r;
	v1.x = 4;
	v1.y = 5;
	v1.z = 7;
	v2.x = 8;
	v2.y = 2;
	v2.z = 1;
	r = engine3D_vector3f_div(v1, v2);
	ck_assert_float_eq_tol(0.5f, r.x, 0.1f);
	ck_assert_float_eq_tol(2.5f, r.y, 0.1f);
	ck_assert_float_eq_tol(7.0f, r.z, 0.1f);
}
END_TEST;

START_TEST(Vector3fDivfTest) {
	engine3D_vector3f_t v, r;
	v.x = 4;
	v.y = 5;
	v.z = 7;
	r = engine3D_vector3f_divf(v, 3);
	ck_assert_float_eq_tol(1.3f, r.x, 0.1f);
	ck_assert_float_eq_tol(1.6f, r.y, 0.1f);
	ck_assert_float_eq_tol(2.3f, r.z, 0.1f);
}
END_TEST;

START_TEST(Vector3fLerpTest) {
  engine3D_vector3f_t v1, v2, r;
  v1.x = 4;
  v1.y = 9;
  v1.z = 1;
  v2.x = 1;
  v2.y = 3;
  v2.z = 8;
  r = engine3D_vector3f_lerp(v1, v2, 0.5f);
  ck_assert_float_eq_tol(2.5f, r.x, 0.1f);
  ck_assert_float_eq_tol(6.0f, r.y, 0.1f);
  ck_assert_float_eq_tol(4.5f, r.z, 0.1f);
}
END_TEST;

START_TEST(Vector3fEqualTest) {
  engine3D_vector3f_t v1, v2;
  v1.x = 4;
  v1.y = 9;
  v1.z = 1;
  v2.x = 1;
  v2.y = 3;
  v2.z = 8;
  ck_assert(!engine3D_vector3f_equal(v1, v2));
  v2.x = 4;
  v2.y = 9;
  v2.z = 1;
  ck_assert(engine3D_vector3f_equal(v1, v2));
}
END_TEST;

START_TEST(Vector3fSwizzlingTest) {
  engine3D_vector3f_t v = { 10, 20, 30 };
  engine3D_vector2f_t r;
  
  r = engine3D_vector3f_xy(v);
  ck_assert_float_eq(10.0f, r.x);
  ck_assert_float_eq(20.0f, r.y);
  
  r = engine3D_vector3f_yz(v);
  ck_assert_float_eq(20.0f, r.x);
  ck_assert_float_eq(30.0f, r.y);
  
  r = engine3D_vector3f_xz(v);
  ck_assert_float_eq(10.0f, r.x);
  ck_assert_float_eq(30.0f, r.y);
  
  r = engine3D_vector3f_yx(v);
  ck_assert_float_eq(20.0f, r.x);
  ck_assert_float_eq(10.0f, r.y);
  
  r = engine3D_vector3f_zy(v);
  ck_assert_float_eq(30.0f, r.x);
  ck_assert_float_eq(20.0f, r.y);
  
  r = engine3D_vector3f_zx(v);
  ck_assert_float_eq(30.0f, r.x);
  ck_assert_float_eq(10.0f, r.y);
}
END_TEST;

START_TEST(Matrix4fIdentityTest) {
	engine3D_matrix4f_t m;
	engine3D_matrix4f_setIdentity(&m);

	ck_assert_float_eq(1.0f, m.mat[0][0]);
	ck_assert_float_eq(0.0f, m.mat[0][1]);
	ck_assert_float_eq(0.0f, m.mat[0][2]);
	ck_assert_float_eq(0.0f, m.mat[0][3]);

	ck_assert_float_eq(0.0f, m.mat[1][0]);
	ck_assert_float_eq(1.0f, m.mat[1][1]);
	ck_assert_float_eq(0.0f, m.mat[1][2]);
	ck_assert_float_eq(0.0f, m.mat[1][3]);

	ck_assert_float_eq(0.0f, m.mat[2][0]);
	ck_assert_float_eq(0.0f, m.mat[2][1]);
	ck_assert_float_eq(1.0f, m.mat[2][2]);
	ck_assert_float_eq(0.0f, m.mat[2][3]);

	ck_assert_float_eq(0.0f, m.mat[3][0]);
	ck_assert_float_eq(0.0f, m.mat[3][1]);
	ck_assert_float_eq(0.0f, m.mat[3][2]);
	ck_assert_float_eq(1.0f, m.mat[3][3]);
}
END_TEST;

START_TEST(Matrix4fMulTest) {
	engine3D_matrix4f_t m1, m2, r;

	m1.mat[0][0] = 3;		m2.mat[0][0] = 5;
	m1.mat[0][1] = 8;		m2.mat[0][1] = 6;
	m1.mat[0][2] = 7;		m2.mat[0][2] = 8;
	m1.mat[0][3] = 5;		m2.mat[0][3] = 0;

	m1.mat[1][0] = 2;		m2.mat[1][0] = 0;
	m1.mat[1][1] = 6;		m2.mat[1][1] = 7;
	m1.mat[1][2] = 8;		m2.mat[1][2] = 4;
	m1.mat[1][3] = 0;		m2.mat[1][3] = 2;

	m1.mat[2][0] = 9;		m2.mat[2][0] = 2;
	m1.mat[2][1] = 6;		m2.mat[2][1] = 5;
	m1.mat[2][2] = 4;		m2.mat[2][2] = 6;
	m1.mat[2][3] = 6;		m2.mat[2][3] = 8;

	m1.mat[3][0] = 8;		m2.mat[3][0] = 0;
	m1.mat[3][1] = 6;		m2.mat[3][1] = 8;
	m1.mat[3][2] = 8;		m2.mat[3][2] = 5;
	m1.mat[3][3] = 6;		m2.mat[3][3] = 4;

	engine3D_matrix4f_mul(&m1, &m2, &r);

	ck_assert_float_eq(29.0f, r.mat[0][0]);
	ck_assert_float_eq(149.0f, r.mat[0][1]);
	ck_assert_float_eq(123.0f, r.mat[0][2]);
	ck_assert_float_eq(92.0f, r.mat[0][3]);

	ck_assert_float_eq(26.0f, r.mat[1][0]);
	ck_assert_float_eq(94.0f, r.mat[1][1]);
	ck_assert_float_eq(88.0f, r.mat[1][2]);
	ck_assert_float_eq(76.0f, r.mat[1][3]);

	ck_assert_float_eq(53.0f, r.mat[2][0]);
	ck_assert_float_eq(164.0f, r.mat[2][1]);
	ck_assert_float_eq(150.0f, r.mat[2][2]);
	ck_assert_float_eq(68.0f, r.mat[2][3]);

	ck_assert_float_eq(56.0f, r.mat[3][0]);
	ck_assert_float_eq(178.0f, r.mat[3][1]);
	ck_assert_float_eq(166.0f, r.mat[3][2]);
	ck_assert_float_eq(100.0f, r.mat[3][3]);
}
END_TEST;

START_TEST(QuaternionLengthTest) {
	engine3D_quaternion_t v;
	v.x = 3;
	v.y = 1;
	v.z = 2;
	v.w = 7;
	float r = engine3D_quaternion_length(&v);
	ck_assert_float_eq_tol(7.937f, r, 0.001f);
}
END_TEST;

START_TEST(QuaternionNormalizeTest) {
	engine3D_quaternion_t v;
	v.x = 3;
	v.y = 1;
	v.z = 2;
	v.w = 7;
	engine3D_quaternion_normalize(&v);
	ck_assert_float_eq_tol(0.378f, v.x, 0.001f);
	ck_assert_float_eq_tol(0.125f, v.y, 0.001f);
	ck_assert_float_eq_tol(0.251f, v.z, 0.001f);
	ck_assert_float_eq_tol(0.882f, v.w, 0.001f);
}
END_TEST;

START_TEST(QuaternionConjugateTest) {
	engine3D_quaternion_t v, r;
	v.x = 5;
	v.y = 2;
	v.z = 7;
	v.w = 6;
	engine3D_quaternion_conjugate(&v, &r);
	ck_assert_float_eq(-5.0f, r.x);
	ck_assert_float_eq(-2.0f, r.y);
	ck_assert_float_eq(-7.0f, r.z);
	ck_assert_float_eq(6.0f, r.w);
}
END_TEST;

START_TEST(QuaternionMulTest) {
	engine3D_quaternion_t v1, v2, r;

	v1.x = 5;		 v2.x = 9;
	v1.y = 2;		 v2.y = 4;
	v1.z = 7;		 v2.z = 1;
	v1.w = 6;		 v2.w = 4;

	engine3D_quaternion_mul(&v1, &v2, &r);

	ck_assert_float_eq(48.0f, r.x);
	ck_assert_float_eq(90.0f, r.y);
	ck_assert_float_eq(36.0f, r.z);
	ck_assert_float_eq(-36.0f, r.w);
}
END_TEST;

START_TEST(QuaternionMulvTest) {
	engine3D_quaternion_t v1, r;
	engine3D_vector3f_t v2;

	v1.x = 5;		 v2.x = 9;
	v1.y = 2;		 v2.y = 4;
	v1.z = 7;		 v2.z = 1;
	v1.w = 6;

	engine3D_quaternion_mulv(&v1, v2, &r);

	ck_assert_float_eq(28.0f, r.x);
	ck_assert_float_eq(82.0f, r.y);
	ck_assert_float_eq(8.0f, r.z);
	ck_assert_float_eq(-60.0f, r.w);
}
END_TEST;

Suite *makeSuite(void) {
	Suite *s = suite_create("Base");

	TCase *tc_growingArray = tcase_create("GrowingArray");
	tcase_add_test(tc_growingArray, GrowingArrayWithFinish);
	tcase_add_test(tc_growingArray, GrowingArrayWithoutFinish);
	suite_add_tcase(s, tc_growingArray);

	TCase *tc_strToIntMap = tcase_create("StrToIntMap");
	tcase_add_test(tc_strToIntMap, StrToIntMapNoCollision);
	tcase_add_test(tc_strToIntMap, StrToIntMapWithCollision);
	suite_add_tcase(s, tc_strToIntMap);

	TCase *tc_time = tcase_create("Time");
	tcase_add_test(tc_time, GetTimeTest);
	suite_add_tcase(s, tc_time);

	TCase *tc_vector = tcase_create("Vector");
	tcase_add_test(tc_vector, Vector2fLengthTest);
	tcase_add_test(tc_vector, Vector2fDotTest);
	tcase_add_test(tc_vector, Vector2fCrossTest);
	tcase_add_test(tc_vector, Vector2fNormalizeTest);
	tcase_add_test(tc_vector, Vector2fRotateTest);
	tcase_add_test(tc_vector, Vector2fAddTest);
	tcase_add_test(tc_vector, Vector2fAddfTest);
	tcase_add_test(tc_vector, Vector2fSubTest);
	tcase_add_test(tc_vector, Vector2fSubfTest);
	tcase_add_test(tc_vector, Vector2fMulTest);
	tcase_add_test(tc_vector, Vector2fMulfTest);
	tcase_add_test(tc_vector, Vector2fDivTest);
	tcase_add_test(tc_vector, Vector2fDivfTest);
	tcase_add_test(tc_vector, Vector2fLerpTest);
	tcase_add_test(tc_vector, Vector2fEqualTest);
	tcase_add_test(tc_vector, Vector3fDotTest);
	tcase_add_test(tc_vector, Vector3fNormalizeTest);
	tcase_add_test(tc_vector, Vector3fRotateTest);
	tcase_add_test(tc_vector, Vector3fCrossTest);
	tcase_add_test(tc_vector, Vector3fAddTest);
	tcase_add_test(tc_vector, Vector3fAddfTest);
	tcase_add_test(tc_vector, Vector3fSubTest);
	tcase_add_test(tc_vector, Vector3fSubfTest);
	tcase_add_test(tc_vector, Vector3fMulTest);
	tcase_add_test(tc_vector, Vector3fMulfTest);
	tcase_add_test(tc_vector, Vector3fDivTest);
	tcase_add_test(tc_vector, Vector3fDivfTest);
	tcase_add_test(tc_vector, Vector3fLerpTest);
	tcase_add_test(tc_vector, Vector3fEqualTest);
	tcase_add_test(tc_vector, Vector3fSwizzlingTest);
	tcase_add_test(tc_vector, Matrix4fIdentityTest);
	tcase_add_test(tc_vector, Matrix4fMulTest);
	tcase_add_test(tc_vector, QuaternionLengthTest);
	tcase_add_test(tc_vector, QuaternionNormalizeTest);
	tcase_add_test(tc_vector, QuaternionConjugateTest);
	tcase_add_test(tc_vector, QuaternionMulTest);
	tcase_add_test(tc_vector, QuaternionMulvTest);
	suite_add_tcase(s, tc_vector);

	return s;
}

int main(void) {
	int number_failed;
	Suite *s = makeSuite();
	SRunner *sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
