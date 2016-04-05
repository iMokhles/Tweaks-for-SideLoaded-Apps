//
//  DownloadsTVC.m
//  WAForIpad
//
//  Created by iMokhles on 05/04/16.
//  Copyright © 2016 iMokhles. All rights reserved.
//

#import "DownloadsTVC.h"
#import "TotoaShopHelper.h"
#import <QuickLook/QuickLook.h>
#import "UIImageView+WebCache.h"

@interface DownloadsTVC () <QLPreviewControllerDelegate, QLPreviewControllerDataSource> {
    NSUserDefaults *userDefaults;
    NSArray *itemsArray;
    NSString *staticPath;
}

@end

@implementation DownloadsTVC

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    userDefaults = [NSUserDefaults standardUserDefaults];
    itemsArray = [userDefaults objectForKey:@"fileInfoArray"];
    
}
- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.title = @"Downloads";
    UIBarButtonItem *doneButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(closeThisPage)];
    [self.navigationItem setRightBarButtonItem:doneButton];
    
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}

- (void)closeThisPage {
    [self dismissViewControllerAnimated:YES completion:^{
        
    }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return itemsArray.count;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    NSDictionary *videoInfo  = itemsArray[indexPath.row];
    
    NSURL *urlImg                  = [NSURL URLWithString:videoInfo[@"mediumThumbnailURL"]];
    NSNumber *audioNM = videoInfo[@"isAudio"];
    BOOL isAudio = [audioNM boolValue];
    
    [cell.imageView sd_setImageWithURL:urlImg];
    cell.textLabel.text = videoInfo[@""];
    
    if (isAudio) {
        cell.detailTextLabel.text = [NSString stringWithFormat:@"Audio  -  %@", videoInfo[@"videoDuration"]];
    } else {
        cell.detailTextLabel.text = [NSString stringWithFormat:@"Video  -  %@", videoInfo[@"videoDuration"]];
    }
    
    // Configure the cell...
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    NSDictionary *fileInfo = itemsArray[indexPath.row];
    NSString *filePath;
    NSNumber *audioNM = fileInfo[@"isAudio"];
    BOOL isAudio = [audioNM boolValue];
    if (isAudio == NO) {
        filePath = [[TotoaShopHelper getDownloadsPath] stringByAppendingPathComponent:[NSString stringWithFormat:@"mp4/%@-%@.mp4", fileInfo[@"videoTitle"], fileInfo[@"videoID"]]];
    } else {
        filePath = [[TotoaShopHelper getDownloadsPath] stringByAppendingPathComponent:[NSString stringWithFormat:@"m4a/%@-%@.m4a", fileInfo[@"videoTitle"], fileInfo[@"videoID"]]];
    }
    
    staticPath = filePath;
    QLPreviewController *preview = [[QLPreviewController alloc] init];
    preview.dataSource = self;
    
    [self.navigationController pushViewController:preview animated:YES];
}

#pragma mark - QuickLook

- (BOOL)previewController:(QLPreviewController *)controller shouldOpenURL:(NSURL *)url forPreviewItem:(id <QLPreviewItem>)item {
    
    return YES;
}
- (NSInteger) numberOfPreviewItemsInPreviewController: (QLPreviewController *) controller {
    return 1;
}

- (id <QLPreviewItem>) previewController: (QLPreviewController *) controller previewItemAtIndex: (NSInteger) index {
    return [NSURL fileURLWithPath:staticPath];
}


// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the specified item to be editable.
    return YES;
}



// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    NSDictionary *fileInfo = itemsArray[indexPath.row];
    NSString *filePath;
    
    NSNumber *audioNM = fileInfo[@"isAudio"];
    BOOL isAudio = [audioNM boolValue];
    
    if (isAudio == YES) {
        filePath = [[TotoaShopHelper getDownloadsPath] stringByAppendingPathComponent:[NSString stringWithFormat:@"mp4/%@-%@.mp4", fileInfo[@"videoTitle"], fileInfo[@"videoID"]]];
    } else {
        filePath = [[TotoaShopHelper getDownloadsPath] stringByAppendingPathComponent:[NSString stringWithFormat:@"m4a/%@-%@.m4a", fileInfo[@"videoTitle"], fileInfo[@"videoID"]]];
    }
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [[NSFileManager defaultManager] removeItemAtPath:filePath error:NULL];
        NSMutableArray *loadDefects = [itemsArray mutableCopy];
        [loadDefects removeObjectAtIndex:indexPath.row];
        [userDefaults setObject:loadDefects forKey:@"fileInfoArray"];
        [userDefaults synchronize];
        
        [[itemsArray mutableCopy] removeAllObjects];
        itemsArray = [userDefaults objectForKey:@"fileInfoArray"];
        [self.tableView reloadData];
        //[tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    } 
}


/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
