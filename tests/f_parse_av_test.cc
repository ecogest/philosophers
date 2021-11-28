/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse_av_test.cc                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:05:05 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/28 16:45:59 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <tuple>
#include <vector>

extern "C" {
#include "philo.h"
}

// ARGS NUMERIC AND POSITIVE
// PHILOS COUNT STRICTLY POSITIVE
// ARGS < SIZE_T_MAX

/*
** ========================== Google Test Fixture =========================== **
*/

class	AvErrorTest: public ::testing::TestWithParam<std::tuple<t_error,int,std::vector<const char *>>> {
	public:
		t_error	actual_err;
		t_error	theoritical_err;
		AvErrorTest() {
			t_all	all;
			int		ac              = std::get<1>(GetParam());
			const char	* const *av = std::get<2>(GetParam()).data();
			theoritical_err         = std::get<0>(GetParam());
			f_parse_av(&all, ac, (const char **)av);
			actual_err = all.error;
		}
};

/*
** ================================= TESTS ================================== **
*/

TEST_P(AvErrorTest, all) {
	EXPECT_EQ(actual_err, theoritical_err);
}

/*
** ============================== INSTANTIATE =============================== **
*/

#define T std::make_tuple<t_error,int,std::vector<const char *>>

INSTANTIATE_TEST_SUITE_P(AvErrorTestSuite, AvErrorTest,
		::testing::Values(
			// ARGS == 3 OU 4 (ac = 4 ou 5)
			T(error_av, 2, {"./philo","42"}),
			T(success, 3, {"./philo","42", "42"}),
			T(error_av, 6, {"./philo","42", "42", "42", "42", "42"}),
			T(success, 4, {"./philo","42", "42", "42"}),
			T(success, 5, {"./philo","42", "42", "42", "42"})
			));
