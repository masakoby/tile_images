#include <iostream>

#include "kb_searchfiles.h"
#include "kb_searchfolders.h"
#include <opencv2/opencv.hpp>
#include "kb_split_string.h"
#include "kb_cv_string.h"
#include "kb_cv_arrange_cvmat.h"

int main(int argc, char* argv[])
{
	std::string dname_image = argv[1];
	std::string key1 = "*.png";
	std::string dname_out = argv[2];
	int step_folder = 15;
	int step_image = 20;
	int width_tile = 96;

	dname_image += "\\";

	std::vector<std::string> vfolder;
	kb::search_folders(dname_image, "*", vfolder);
	int num_folders = vfolder.size();
	{
		std::vector<std::string> vfolder2;

		std::map<int, std::string> m1;
		for (int k = 0; k < num_folders; k++) {
			m1.insert(std::pair<int, std::string>(std::stoi(vfolder[k]), vfolder[k]));
		}
		std::map<int, std::string>::iterator it = m1.begin();
		while (it != m1.end()) {
			vfolder2.push_back(it->second);
			it++;
		}
		vfolder = vfolder2;
	}

	int k_num = num_folders / step_folder + 1;
	for (int k = 0; k < k_num; k++) {

		std::vector<cv::Mat> vmat;
		vmat.resize(step_folder * step_image);

		for (int k2 = 0; k2 < step_folder; k2++) {
			int kk2 = k2 + k * step_folder;
			if (kk2 >= num_folders)
				break;

			std::string dname = dname_image + vfolder[kk2] + "\\";
			std::cout << dname << std::endl;

			std::vector<std::string> vfile;
			kb::search_files(dname, key1.c_str(), vfile);
			int num_file = vfile.size();
			for (int j = 0; j < step_image; j++) {
				if (j >= num_file)
					break;

				vmat[k2 * step_image + j] = cv::imread(dname+vfile[j]);
			}
		}

		cv::Mat matV;
		kb::arrange_matN(vmat, matV, step_image, step_folder, width_tile);

		std::string path_out = dname_out + vfolder[k*step_folder]+".jpg";
		cv::imwrite(path_out, matV);
	}

	return 0;
}
