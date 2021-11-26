/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello_world_test.cc                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:20:51 by mjacq             #+#    #+#             */
/*   Updated: 2021/11/26 13:13:24 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>

extern "C" {
#include "hello_world.h"
}

TEST(hello_world, returns_zero) {
	ASSERT_EQ(hello_world(), 0);
}

TEST(hello_world, returns_one) {
	GTEST_SKIP();
	ASSERT_EQ(hello_world(), 1);
}

TEST(hello_world, output_stdout) {
	testing::internal::CaptureStdout();
	hello_world();
	std::string output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, "Hello world!\n");
}
